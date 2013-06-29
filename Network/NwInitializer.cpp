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

#include <event2/event-config.h>
#include <event2/thread.h>
#include <event2/event.h>
#include "NwInitializer.h"

static void* NwMalloc(size_t size)
{
#ifdef _DEBUG
	return NwInitializer_Alloc::allocate(size, __FILE__, __LINE__);
#else
	return NwInitializer_Alloc::allocate(size);
#endif // _DEBUG
}

static void* NwRealloc(void* p, size_t size)
{
#ifdef _DEBUG
	return NwInitializer_Alloc::reallocate(p, size, __FILE__, __LINE__);
#else
	return NwInitializer_Alloc::reallocate(p, size);
#endif  // _DEBUG
}

static void NwFree(void* p)
{
	NwInitializer_Alloc::deallocate(p);
}

NwInitializer::NwInitializer()
{
#if defined(_WIN32) || defined(_WIN64)
	WSADATA wsa;
	WORD ver = MAKEWORD(2, 2);

	if (WSAStartup(ver, &wsa))
	{
		throw std::runtime_error("WSAStartup error.");
	}

	evthread_use_windows_threads();
#else
	evthread_use_pthreads();
#endif  // _WIN32 || _WIN64

	event_set_mem_functions(NwMalloc, NwRealloc, NwFree);
}

NwInitializer::~NwInitializer()
{
#if defined(_WIN32) || defined(_WIN64)
	WSACleanup();
#endif  // _WIN32 || _WIN64
}
