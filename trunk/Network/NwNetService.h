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

#include "Memory/STLAllocator.h"
#include "NwEventDispatcher.h"
#include "NwMessageFilter.h"
#include "NwListener.h"
#include <list>

class NwEventHandler;

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define NwNetService_Alloc	TCMallocAllocator
#else
#define NwNetService_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class NwNetService : public RefObject<NwNetService_Alloc, boost::detail::atomic_count>
{
public:
	typedef std::list<
		NwMessageFilterFactoryPtr,
		STLAllocator<NwMessageFilterFactoryPtr, NwNetService_Alloc>
	> NwMessageFilterFactoryList;

public:
	NwNetService(NwEventDispatcher* dispatcher, NwEventHandler* handler);
	virtual ~NwNetService();

	void addFilterFactory(NwMessageFilterFactoryPtr factory);

	bool connect(const char* addr, int port);
	NwListenerPtr listen(const char* ip, int port, int backlog = -1);

	// Internal functionos
	NwEventDispatcher* dispatcher() const;
	NwEventHandler* handler() const;
	const NwMessageFilterFactoryList& factories() const;

private:
	NwEventDispatcherPtr mDispatcher;
	NwEventHandler* mHandler;

	NwMessageFilterFactoryList mFactories;
};

DeclareSmartPointer(NwNetService);

#endif  // __Network_NwNetService_H__
