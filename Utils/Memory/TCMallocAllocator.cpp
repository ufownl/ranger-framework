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

#include "Memory/TCMallocAllocator.h"
#include "Memory/MemoryLeakDetector.h"
#include <limits>
#include <tcmalloc.h>

#ifdef _DEBUG

void* TCMallocAllocator::allocate(size_t size, const char* file, long line)
{
	void* p = tc_malloc(size);
	MemoryLeakDetectorHolder::instance().onAllocate(p, size, file, line);
	return p;
}

void TCMallocAllocator::deallocate(void* p)
{
	MemoryLeakDetectorHolder::instance().onDeallocate(p);
	tc_free(p);
}

#else

void* TCMallocAllocator::allocate(size_t size)
{
	return tc_malloc(size);
}

void TCMallocAllocator::deallocate(void* p)
{
	tc_free(p);
}

#endif  // _DEBUG

void TCMallocAllocator::deallocate(void* p, size_t)
{
	deallocate(p);
}

size_t TCMallocAllocator::max_size()
{
	return std::numeric_limits<size_t>::max();
}
