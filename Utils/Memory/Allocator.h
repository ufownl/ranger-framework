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

#ifndef __Utils_Memory_Allocator_H__
#define __Utils_Memory_Allocator_H__

#include "Object/Singleton.h"
#include <stddef.h>

class Allocator
{
public:
#ifdef _DEBUG
    static void* allocate(size_t size, const char* file, long line);
	static void* reallocate(void* old, size_t size, const char* file, long line);
#else
    static void* allocate(size_t size);
	static void* reallocate(void* old, size_t size);
#endif  // _DEBUG

    static void deallocate(void* p);
	static void deallocate(void* p, size_t);

	static size_t max_size();
};

#endif  // __Utils_Memory_Allocator_H__
