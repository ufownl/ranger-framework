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

#ifndef __Network_NwEventDispatcher_H__
#define __Network_NwEventDispatcher_H__

#include "NwInitializer.h"

struct event_base;

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define NwEventDispatcher_Alloc	TCMallocAllocator
#else
#define NwEventDispatcher_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class NwEventDispatcher : public RefObject<NwEventDispatcher_Alloc, boost::detail::atomic_count>
{
public:
	NwEventDispatcher(int cpus = 0);
	virtual ~NwEventDispatcher();

	int dispatch();
	int dispatchOnce(bool block = true);
	void exit(float sec = 0.0f);
	void quit();

	event_base* backend() const;

private:
	NwInitializerPtr mInitializer;
	event_base* mBackend;
};

DeclareSmartPointer(NwEventDispatcher);

#endif  // __Network_NwEventDispatcher_H__
