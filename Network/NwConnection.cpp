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
#include <stdio.h>
#if !defined(_WIN32) && !defined(_WIN64)
#include <arpa/inet.h>
#include <errno.h>
#endif  // !_WIN32 && !_WIN64

static bufferevent_filter_result filter_input_cb(
	evbuffer* source, evbuffer* destination, ev_ssize_t limit, bufferevent_flush_mode mode, void *ctx)
{
	try
	{
		NwBufferBasePtr src = RfNew NwBufferBase(source);
		NwBufferBasePtr dst = RfNew NwBufferBase(destination);

		switch (static_cast<NwMessageFilter*>(ctx)->decode(src, dst))
		{
		case NwMessageFilter::eOK:
			return BEV_OK;
		case NwMessageFilter::eMORE:
			return BEV_NEED_MORE;
		default:
			return BEV_ERROR;
		}
	}
	catch (const std::invalid_argument& e)
	{
		fprintf(stderr, "invalid_argument: %s\n", e.what());
		return BEV_ERROR;
	}
	catch (const std::bad_alloc& e)
	{
		fprintf(stderr, "bad_alloc: %s\n", e.what());
		return BEV_ERROR;
	}
	catch (const std::exception& e)
	{
		fprintf(stderr, "exception: %s\n", e.what());
		return BEV_ERROR;
	}
}

static bufferevent_filter_result filter_output_cb(
	evbuffer* source, evbuffer* destination, ev_ssize_t limit, bufferevent_flush_mode mode, void *ctx)
{
	try
	{
		NwBufferBasePtr src = RfNew NwBufferBase(source);
		NwBufferBasePtr dst = RfNew NwBufferBase(destination);

		switch (static_cast<NwMessageFilter*>(ctx)->encode(src, dst))
		{
		case NwMessageFilter::eOK:
			return BEV_OK;
		case NwMessageFilter::eMORE:
			return BEV_NEED_MORE;
		default:
			return BEV_ERROR;
		}
	}
	catch (const std::invalid_argument& e)
	{
		fprintf(stderr, "invalid_argument: %s\n", e.what());
		return BEV_ERROR;
	}
	catch (const std::bad_alloc& e)
	{
		fprintf(stderr, "bad_alloc: %s\n", e.what());
		return BEV_ERROR;
	}
	catch (const std::exception& e)
	{
		fprintf(stderr, "exception: %s\n", e.what());
		return BEV_ERROR;
	}
}

static void read_cb(bufferevent* bev, void* ctx)
{
	try
	{
		NwConnectionPtr conn = static_cast<NwConnection*>(ctx);
		NwBufferBasePtr buf = RfNew NwBufferBase(bufferevent_get_input(bev));
		conn->handler()->onRead(conn, buf);
	}
	catch (const std::invalid_argument& e)
	{
		fprintf(stderr, "invalid_argument: %s\n", e.what());
	}
	catch (const std::bad_alloc& e)
	{
		fprintf(stderr, "bad_alloc: %s\n", e.what());
	}
	catch (const std::exception& e)
	{
		fprintf(stderr, "exception: %s\n", e.what());
	}
}

static void event_cb(bufferevent* bev, short events, void* ctx)
{
	try
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
	catch (const std::invalid_argument& e)
	{
		fprintf(stderr, "invalid_argument: %s\n", e.what());
	}
	catch (const std::bad_alloc& e)
	{
		fprintf(stderr, "bad_alloc: %s\n", e.what());
	}
	catch (const std::exception& e)
	{
		fprintf(stderr, "exception: %s\n", e.what());
	}
}

bool NwConnection::write(const void* data, size_t len)
{
	if (!mBackend.frontend)
	{
		return false;
	}

	return bufferevent_write(mBackend.frontend, data, len) == 0;
}

bool NwConnection::write(NwBufferBase* buf)
{
	if (!mBackend.frontend)
	{
		return false;
	}
	
	return bufferevent_write_buffer(mBackend.frontend, buf->backend()) == 0;
}

bool NwConnection::setRateLimit(size_t rr, size_t rb, size_t wr, size_t wb)
{
	if (!mBackend.backend)
	{
		return false;
	}

	if (mBackend.rate)
	{
		bufferevent_set_rate_limit(mBackend.backend, 0);
		ev_token_bucket_cfg_free(mBackend.rate);
	}

	mBackend.rate = ev_token_bucket_cfg_new(rr, rb, wr, wb, 0);

	if (!mBackend.rate)
	{
		return false;
	}

	bufferevent_set_rate_limit(mBackend.backend, mBackend.rate);
	return true;
}

bool NwConnection::setRateLimit(size_t rr, size_t rb, size_t wr, size_t wb, float sec)
{
	if (!mBackend.backend)
	{
		return false;
	}

	if (mBackend.rate)
	{
		bufferevent_set_rate_limit(mBackend.backend, 0);
		ev_token_bucket_cfg_free(mBackend.rate);
	}

	timeval tv;

	tv.tv_sec = static_cast<long>(sec);
	tv.tv_usec = static_cast<long>((sec - tv.tv_sec) * 1000000);

	mBackend.rate = ev_token_bucket_cfg_new(rr, rb, wr, wb, &tv);

	if (!mBackend.rate)
	{
		return false;
	}

	bufferevent_set_rate_limit(mBackend.backend, mBackend.rate);
	return true;
}

size_t NwConnection::getReadLimit() const
{
	if (!mBackend.backend)
	{
		return EV_SSIZE_MAX;
	}

	return bufferevent_get_read_limit(mBackend.backend);
}

size_t NwConnection::getWriteLimit() const
{
	if (!mBackend.backend)
	{
		return EV_SSIZE_MAX;
	}

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

NwConnection::NwConnection(NwEventHandler* handler)
	: mHandler(handler)
	, mPort(0)
	, mExtra(0)
{
	mBackend.backend = 0;
	mBackend.frontend = 0;
	mBackend.rate = 0;
}

NwConnection::~NwConnection()
{
	shutdown();
}

bool NwConnection::initialize(bufferevent* bev)
{
	if (!bev)
	{
		return false;
	}

	if (!mHandler)
	{
		bufferevent_free(bev);
		return false;
	}

	shutdown();

	bufferevent_setcb(bev, read_cb, 0, event_cb, this);
	bufferevent_enable(bev, EV_READ | EV_WRITE);

	mBackend.backend = bev;
	mBackend.frontend = bev;
	mBackend.rate = 0;

	sockaddr_in addr;
	socklen_t len = sizeof(addr);

	getpeername(bufferevent_getfd(bev), (sockaddr*)&addr, &len);
	mIP = inet_ntoa(addr.sin_addr);
	mPort = ntohs(addr.sin_port);

	return true;
}

void NwConnection::shutdown()
{
	if (mBackend.frontend)
	{
		bufferevent_free(mBackend.frontend);
		mBackend.frontend = 0;
		mBackend.backend = 0;
	}

	if (mBackend.rate)
	{
		ev_token_bucket_cfg_free(mBackend.rate);
		mBackend.rate = 0;
	}

	mFilters.clear();
}

bool NwConnection::addFilter(NwMessageFilterPtr filter)
{
	if (!filter || !mBackend.frontend)
	{
		return false;
	}

	bufferevent* frontend = bufferevent_filter_new(
		mBackend.frontend, filter_input_cb, filter_output_cb,
		BEV_OPT_CLOSE_ON_FREE | BEV_OPT_THREADSAFE | BEV_OPT_UNLOCK_CALLBACKS | BEV_OPT_DEFER_CALLBACKS,
		0, filter.data());

	if (!frontend)
	{
		return false;
	}

	bufferevent_setcb(frontend, read_cb, 0, event_cb, this);
	bufferevent_enable(frontend, EV_READ | EV_WRITE);

	mBackend.frontend = frontend;

	mFilters.push_back(filter);

	return true;
}

const NwConnection::Backend* NwConnection::backend() const
{
	return &mBackend;
}

NwEventHandler* NwConnection::handler() const
{
	return mHandler;
}
