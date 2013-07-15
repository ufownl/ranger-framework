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

#ifndef __Network_NwNetService_H__
#define __Network_NwNetService_H__

#include "NwEventDispatcher.h"
#include "NwMessageFilter.h"

class NwEventHandler;
class NwListener;

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define NwNetService_Alloc	TCMallocAllocator
#else
#define NwNetService_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class NwNetService : public RefObject<NwNetService_Alloc, boost::detail::atomic_count>
{
public:
	NwNetService(NwEventDispatcher* dispatcher, NwMessageFilterFactory* factory, NwEventHandler* handler);
	virtual ~NwNetService();

	bool connect(const char* addr, int port);
	NwListener* listen(const char* ip, int port, int backlog = -1);

	// Internal functionos
	NwEventDispatcher* dispatcher() const;
	NwMessageFilterFactory* factory() const;
	NwEventHandler* handler() const;

private:
	NwEventDispatcherPtr mDispatcher;
	NwMessageFilterFactoryPtr mFactory;
	NwEventHandler* mHandler;
};

DeclareSmartPointer(NwNetService);

#endif  // __Network_NwNetService_H__
