/*	Copyright 2013 RangerUFO
 *
 *	This file is part of RangerFramework.
 *
 *	RangerFramework is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	RangerFramework is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public License
 *	along with RangerFramework.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <event2/event.h>
#include <event2/bufferevent.h>
#include "NwConnection.h"
#include "NwEventHandler.h"
#include "NwBufferBase.h"
#include <stdexcept>
#if !defined(_WIN32) && !defined(_WIN64)
#include <arpa/inet.h>
#include <errno.h>
#endif  // !_WIN32 && !_WIN64

static bufferevent_filter_result filter_input_cb(
	evbuffer* source, evbuffer* destination, ev_ssize_t limit, bufferevent_flush_mode mode, void *ctx)
{
	NwBufferBasePtr src = RfNew NwBufferBase(source);
	NwBufferBasePtr dst = RfNew NwBufferBase(destination);

	switch (static_cast<NwConnection*>(ctx)->filter()->decode(src, dst))
	{
	case NwMessageFilter::eOK:
		return BEV_OK;
	case NwMessageFilter::eMORE:
		return BEV_NEED_MORE;
	default:
		return BEV_ERROR;
	}
}

static bufferevent_filter_result filter_output_cb(
	evbuffer* source, evbuffer* destination, ev_ssize_t limit, bufferevent_flush_mode mode, void *ctx)
{
	NwBufferBasePtr src = RfNew NwBufferBase(source);
	NwBufferBasePtr dst = RfNew NwBufferBase(destination);

	switch (static_cast<NwConnection*>(ctx)->filter()->encode(src, dst))
	{
	case NwMessageFilter::eOK:
		return BEV_OK;
	case NwMessageFilter::eMORE:
		return BEV_NEED_MORE;
	default:
		return BEV_ERROR;
	}
}

static void read_cb(bufferevent* bev, void* ctx)
{
	NwConnectionPtr conn = static_cast<NwConnection*>(ctx);
	NwBufferBasePtr buf = RfNew NwBufferBase(bufferevent_get_input(bev));
	conn->handler()->onRead(conn, buf);
}

static void event_cb(bufferevent* bev, short events, void* ctx)
{
	NwConnectionPtr conn = static_cast<NwConnection*>(ctx);

	if (events & BEV_EVENT_ERROR)
	{
		int errcode = EVUTIL_SOCKET_ERROR();
		const char* err = "No error.";

		if (errcode)
		{
			err = evutil_socket_error_to_string(errcode);
		}

		conn->handler()->onError(conn, err);
		return;
	}

	if (events & BEV_EVENT_TIMEOUT)
	{
		conn->handler()->onTimeout(conn);
		return;
	}

	if (events & BEV_EVENT_EOF)
	{
		conn->handler()->onEof(conn);
		return;
	}
}

NwConnection::NwConnection(bufferevent* bev, NwMessageFilter* filter, NwEventHandler* handler)
	: mFilter(filter)
	, mHandler(handler)
	, mExtra(0)
{
	if (!bev)
	{
		throw std::invalid_argument("Invalid bev.");
	}

	if (!filter)
	{
		bufferevent_free(bev);
		throw std::invalid_argument("Invalid filter.");
	}

	if (!handler)
	{
		bufferevent_free(bev);
		throw std::invalid_argument("Invalid handler.");
	}

	mBackend.backend = bev;
	mBackend.filter = bufferevent_filter_new(
		bev, filter_input_cb, filter_output_cb,
		BEV_OPT_CLOSE_ON_FREE | BEV_OPT_THREADSAFE | BEV_OPT_UNLOCK_CALLBACKS | BEV_OPT_DEFER_CALLBACKS,
		0, this);
	mBackend.rate = 0;

	if (!mBackend.filter)
	{
		bufferevent_free(bev);
		throw std::runtime_error("Backend filter creation failed.");
	}

	bufferevent_setcb(mBackend.filter, read_cb, 0, event_cb, this);
	bufferevent_enable(mBackend.filter, EV_READ | EV_WRITE);

	sockaddr_in addr;
	socklen_t len = sizeof(addr);

	getpeername(bufferevent_getfd(bev), (sockaddr*)&addr, &len);
	mIP = inet_ntoa(addr.sin_addr);
	mPort = ntohs(addr.sin_port);
}

NwConnection::~NwConnection()
{
	if (mBackend.filter)
	{
		bufferevent_free(mBackend.filter);
	}

	if (mBackend.rate)
	{
		ev_token_bucket_cfg_free(mBackend.rate);
	}
}

bool NwConnection::write(const void* data, size_t len)
{
	return bufferevent_write(mBackend.filter, data, len) == 0;
}

bool NwConnection::write(NwBufferBase* buf)
{
	return bufferevent_write_buffer(mBackend.filter, buf->backend()) == 0;
}

void NwConnection::setRateLimit(size_t rr, size_t rb, size_t wr, size_t wb)
{
	if (mBackend.rate)
	{
		bufferevent_set_rate_limit(mBackend.backend, 0);
		ev_token_bucket_cfg_free(mBackend.rate);
	}

	mBackend.rate = ev_token_bucket_cfg_new(rr, rb, wr, wb, 0);

	if (mBackend.rate)
	{
		bufferevent_set_rate_limit(mBackend.backend, mBackend.rate);
	}
}

void NwConnection::setRateLimit(size_t rr, size_t rb, size_t wr, size_t wb, float sec)
{
	if (mBackend.rate)
	{
		bufferevent_set_rate_limit(mBackend.backend, 0);
		ev_token_bucket_cfg_free(mBackend.rate);
	}

	timeval tv;

	tv.tv_sec = static_cast<long>(sec);
	tv.tv_usec = static_cast<long>((sec - tv.tv_sec) * 1000000);

	mBackend.rate = ev_token_bucket_cfg_new(rr, rb, wr, wb, &tv);

	if (mBackend.rate)
	{
		bufferevent_set_rate_limit(mBackend.backend, mBackend.rate);
	}
}

int NwConnection::getReadLimit() const
{
	return bufferevent_get_read_limit(mBackend.backend);
}

int NwConnection::getWriteLimit() const
{
	return bufferevent_get_write_limit(mBackend.backend);
}

const char* NwConnection::getPeerIP() const
{
	return mIP.c_str();
}

int NwConnection::getPeerPort() const
{
	return mPort;
}

void NwConnection::setExtraData(void* extra)
{
	mExtra = extra;
}

void* NwConnection::getExtraData() const
{
	return mExtra;
}

const NwConnection::Backend* NwConnection::backend() const
{
	return &mBackend;
}

NwMessageFilter* NwConnection::filter() const
{
	return mFilter;
}

NwEventHandler* NwConnection::handler() const
{
	return mHandler;
}
