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

#ifndef __Network_NwInitializer_H__
#define __Network_NwInitializer_H__

#include "Object/Singleton.h"
#include "Object/RefObject.h"
#include "Object/SmartPointer.h"
#include <boost/detail/atomic_count.hpp>

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define NwInitializer_Alloc	TCMallocAllocator
#else
#define NwInitializer_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class NwInitializer
	: public Singleton<NwInitializer>
	, public RefObject<NwInitializer_Alloc, boost::detail::atomic_count>
{
public:
	NwInitializer();
	virtual ~NwInitializer();
};

DeclareSmartPointer(NwInitializer);

#endif  // __Network_NwInitializer_H__
