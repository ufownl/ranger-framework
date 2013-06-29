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

#include "NwMessageFilter.h"
#include "NwEventHandler.h"
#include "NwBuffer.h"
#include "NwConnection.h"
#include "NwEventDispatcher.h"
#include "NwNetService.h"
#include "NwListener.h"
#include <boost/unordered_set.hpp>
#include <stdexcept>
#include <stdio.h>
#include <string.h>

class SampleFilter : public NwMessageFilter
{
public:
	virtual result decode(NwBufferBase* src, NwBufferBase* dst)
	{
		return dst->append(src) ? eOK : eERROR;
	}
};

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define ChatServer_Alloc	TCMallocAllocator
#else
#define ChatServer_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class ChatServer
	: public NwEventHandler
	, public RefObject<ChatServer_Alloc, boost::detail::atomic_count>
{
public:
	ChatServer(NwEventDispatcher* dispatcher)
		: mDispatcher(dispatcher)
	{
		if (!dispatcher)
		{
			throw std::invalid_argument("Invalid dispatcher.");
		}
	}

	virtual void onAccept(NwConnection* conn)
	{
		NwBufferPtr msg = RfNew NwBuffer;

		msg->printf("Welcome %s:%d to chat server, enter 'quit' to quit.\r\n", conn->getPeerIP(), conn->getPeerPort());
		conn->write(msg);

		for (ConnectionSet::iterator i = mConnections.begin(); i != mConnections.end(); ++i)
		{
			msg->printf("SYS: %s:%d online.\r\n", conn->getPeerIP(), conn->getPeerPort());
			(*i)->write(msg);
		}

		mConnections.insert(conn);
	}

	virtual void onRead(NwConnection* conn, NwBufferBase* buf)
	{
		for (char* line = buf->readln(); line; buf->free(line), line = buf->readln())
		{
			if (strcmp(line, "__server_shutdown") == 0)
			{
				mDispatcher->exit();
			}
			else if (strcmp(line, "quit") == 0)
			{
				NwBufferPtr msg = RfNew NwBuffer;

				msg->printf("SYS: Byebye.\r\n");
				conn->write(msg);

				mConnections.erase(conn);

				for (ConnectionSet::iterator i = mConnections.begin(); i != mConnections.end(); ++i)
				{
					msg->printf("SYS: %s:%d normal offline.\r\n", conn->getPeerIP(), conn->getPeerPort());
					(*i)->write(msg);
				}
			}
			else
			{
				NwBufferPtr msg = RfNew NwBuffer;

				for (ConnectionSet::iterator i = mConnections.begin(); i != mConnections.end(); ++i)
				{
					msg->printf("%s:%d say: %s\r\n", conn->getPeerIP(), conn->getPeerPort(), line);
					(*i)->write(msg);
				}
			}
		}
	}

	virtual void onError(NwConnection* conn, const char* err)
	{
		mConnections.erase(conn);

		NwBufferPtr msg = RfNew NwBuffer;

		for (ConnectionSet::iterator i = mConnections.begin(); i != mConnections.end(); ++i)
		{
			msg->printf("SYS: %s:%d error offline.\r\n", conn->getPeerIP(), conn->getPeerPort());
			(*i)->write(msg);
		}
	}

	virtual void onTimeout(NwConnection* conn)
	{
		mConnections.erase(conn);

		NwBufferPtr msg = RfNew NwBuffer;

		for (ConnectionSet::iterator i = mConnections.begin(); i != mConnections.end(); ++i)
		{
			msg->printf("SYS: %s:%d timeout offline.\r\n", conn->getPeerIP(), conn->getPeerPort());
			(*i)->write(msg);
		}
	}

	virtual void onEof(NwConnection* conn)
	{
		mConnections.erase(conn);

		NwBufferPtr msg = RfNew NwBuffer;

		for (ConnectionSet::iterator i = mConnections.begin(); i != mConnections.end(); ++i)
		{
			msg->printf("SYS: %s:%d eof offline.\r\n", conn->getPeerIP(), conn->getPeerPort());
			(*i)->write(msg);
		}
	}

private:
	typedef boost::unordered_set<
		NwConnectionPtr,
		boost::hash<NwConnectionPtr>,
		std::equal_to<NwConnectionPtr>,
		STLAllocator<NwConnectionPtr, ChatServer_Alloc>
	> ConnectionSet;

	ConnectionSet mConnections;
	NwEventDispatcherPtr mDispatcher;
};

DeclareSmartPointer(ChatServer);

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define DisplayClient_Alloc	TCMallocAllocator
#else
#define DisplayClient_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class DisplayClient
	: public NwEventHandler
	, public RefObject<DisplayClient_Alloc, boost::detail::atomic_count>
{
public:
	virtual void onConnect(NwConnection* conn)
	{
		const char* msg = "Hello world! This is chat server, you can`t input anything.\r\n";
		
		conn->write(msg, strlen(msg));
		mConn = conn;

	}

	virtual void onRead(NwConnection* conn, NwBufferBase* buf)
	{
		for (char* line = buf->readln(); line; buf->free(line), line = buf->readln())
		{
			puts(line);
		}
	}

	virtual void onError(NwConnection* conn, const char* error)
	{
		mConn = 0;
	}

	virtual void onTimeout(NwConnection* conn)
	{
		mConn = 0;
	}

	virtual void onEof(NwConnection* conn)
	{
		mConn = 0;
	}

private:
	NwConnectionPtr mConn;
};

DeclareSmartPointer(DisplayClient);

int main(int argc, char* argv[])
{
#if defined(_WIN32) || defined(_WIN64)
	int cpus;

	printf("cpus: ");
	
	if (scanf("%d", &cpus) <= 0)
	{
		return -1;
	}
#endif  // _WIN32 || _WIN64

	int port;

	printf("port: ");

	if (scanf("%d", &port) <= 0)
	{
		return -1;
	}

#if defined(_WIN32) || defined(_WIN64)
	NwEventDispatcherPtr dispatcher = RfNew NwEventDispatcher(cpus);
#else
	NwEventDispatcherPtr dispatcher = RfNew NwEventDispatcher;
#endif  // _WIN32 || _WIN64
	ChatServerPtr server = RfNew ChatServer(dispatcher);
	NwNetServicePtr snet = RfNew NwNetService(dispatcher, createNwMessageFilterFactory<SampleFilter>(), server);
	NwListenerPtr listener = snet->listen(0, port);
	DisplayClientPtr client = RfNew DisplayClient;
	NwNetServicePtr cnet = RfNew NwNetService(dispatcher, createNwMessageFilterFactory<SampleFilter>(), client);

	if (!cnet->connect("localhost", port))
	{
		return -1;
	}

	return dispatcher->dispatch();
}
