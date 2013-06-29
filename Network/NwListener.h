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

#ifndef __Network_NwListener_H__
#define __Network_NwListener_H__

#include "Object/RefObject.h"
#include "Object/SmartPointer.h"
#include <boost/detail/atomic_count.hpp>

struct evconnlistener;

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define NwListener_Alloc	TCMallocAllocator
#else
#define NwListener_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class NwListener : public RefObject<NwListener_Alloc, boost::detail::atomic_count>
{
public:
	NwListener(evconnlistener* listener);
	virtual ~NwListener();

	evconnlistener* backend() const;

private:
	evconnlistener* const mBackend;
};

DeclareSmartPointer(NwListener);

#endif  // __Network_NwListener_H__
