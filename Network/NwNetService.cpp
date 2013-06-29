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
#include <event2/listener.h>
#include "NwNetService.h"
#include "NwEventHandler.h"
#include "NwConnection.h"
#include "NwListener.h"
#include <stdexcept>
#if !defined(_WIN32) && !defined(_WIN64)
#include <arpa/inet.h>
#include <errno.h>
#endif  // !_WIN32 && !_WIN64

static void event_cb(bufferevent* bev, short events, void* ctx)
{
	NwNetService* service = static_cast<NwNetService*>(ctx);
	
	if (events & BEV_EVENT_CONNECTED)
	{
		NwConnectionPtr conn = RfNew NwConnection(
			bev, service->factory()->create<NwMessageFilter>(), service->handler());
		service->handler()->onConnect(conn);
		return;
	}

	if (events & BEV_EVENT_ERROR)
	{
		int errcode = EVUTIL_SOCKET_ERROR();
		const char* err = "No error.";

		if (errcode)
		{
			err = evutil_socket_error_to_string(errcode);
		}

		bufferevent_free(bev);
		service->handler()->onError(0, err);
		return;
	}

	if (events & BEV_EVENT_TIMEOUT)
	{
		bufferevent_free(bev);
		service->handler()->onTimeout(0);
		return;
	}

	if (events & BEV_EVENT_EOF)
	{
		bufferevent_free(bev);
		service->handler()->onEof(0);
		return;
	}
}

static void accept_cb(evconnlistener* listener, evutil_socket_t fd, sockaddr* addr, int socklen, void* ctx)
{
	NwNetService* service = static_cast<NwNetService*>(ctx);
	bufferevent* bev = bufferevent_socket_new(service->dispatcher()->backend(), fd,
		BEV_OPT_CLOSE_ON_FREE | BEV_OPT_THREADSAFE | BEV_OPT_UNLOCK_CALLBACKS | BEV_OPT_DEFER_CALLBACKS);
	NwConnectionPtr conn = RfNew NwConnection(
		bev, service->factory()->create<NwMessageFilter>(), service->handler());

	service->handler()->onAccept(conn);
}

NwNetService::NwNetService(NwEventDispatcher* dispatcher, NwMessageFilterFactory* factory, NwEventHandler* handler)
	: mDispatcher(dispatcher)
	, mFactory(factory)
	, mHandler(handler)
{
	if (!dispatcher)
	{
		throw std::invalid_argument("Invalid dispatcher.");
	}

	if (!factory)
	{
		throw std::invalid_argument("Invalid factory.");
	}

	if (!handler)
	{
		throw std::invalid_argument("Invalid handler.");
	}
}

NwNetService::~NwNetService()
{
}

bool NwNetService::connect(const char* addr, int port)
{
	bufferevent* bev = bufferevent_socket_new(mDispatcher->backend(), -1,
		BEV_OPT_CLOSE_ON_FREE | BEV_OPT_THREADSAFE | BEV_OPT_UNLOCK_CALLBACKS | BEV_OPT_DEFER_CALLBACKS);

	if (bev)
	{
		bufferevent_setcb(bev, 0, 0, event_cb, this);
		bufferevent_enable(bev, EV_READ | EV_WRITE);

		sockaddr_in sin;

		memset(&sin, 0, sizeof(sin));
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = inet_addr(addr);
		sin.sin_port = htons(port);

		if (sin.sin_addr.s_addr == INADDR_NONE)
		{
			return bufferevent_socket_connect_hostname(bev, 0, AF_UNSPEC, addr, port) == 0;
		}
		else
		{
			return bufferevent_socket_connect(bev, (sockaddr*)&sin, sizeof(sin)) == 0;
		}
	}

	return false;
}

NwListener* NwNetService::listen(const char* ip, int port, int backlog /* = -1 */)
{
	sockaddr_in sin;

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;

	if (ip)
	{
		sin.sin_addr.s_addr = inet_addr(ip);
	}
	else
	{
		sin.sin_addr.s_addr = htonl(0);
	}

	sin.sin_port = htons(port);

	evconnlistener* listener = evconnlistener_new_bind(mDispatcher->backend(), accept_cb, this,
		LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE | LEV_OPT_THREADSAFE, backlog, (sockaddr*)&sin, sizeof(sin));

	if (!listener)
	{
		return 0;
	}

	return RfNew NwListener(listener);
}

NwEventDispatcher* NwNetService::dispatcher() const
{
	return mDispatcher;
}

NwMessageFilterFactory* NwNetService::factory() const
{
	return mFactory;
}

NwEventHandler* NwNetService::handler() const
{
	return mHandler;
}
