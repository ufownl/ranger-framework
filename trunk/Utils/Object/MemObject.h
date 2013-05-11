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

#ifndef __Utils_Object_MemObject_H__
#define __Utils_Object_MemObject_H__

#include "Memory/Allocator.h"
#include <exception>
#include <memory>

template <class _Alloc = Allocator>
class MemObject
{
public:
#ifdef _DEBUG

    static void* operator new (size_t size, const char* file, long line)
	{
		if (!size)
		{
			size = 1;
		}

		void* p = _Alloc::getSingleton().allocate(size, file, line);

		if (!p)
		{
			throw std::bad_alloc();
		}

		return p;
	}

    static void* operator new[] (size_t size, const char* file, long line)
	{
		if (!size)
		{
			size = 1;
		}

		void* p = _Alloc::getSingleton().allocate(size, file, line);

		if (!p)
		{
			throw std::bad_alloc();
		}

		return p;
	}

    static void operator delete (void* p, const char*, long)
	{
		if (p)
		{
			_Alloc::getSingleton().deallocate(p);
		}
	}

    static void operator delete[] (void *p, const char*, long)
	{
		if (p)
		{
			_Alloc::getSingleton().deallocate(p);
		}
	}

#else

    static void* operator new (size_t size)
	{
		if (!size)
		{
			size = 1;
		}

		void* p = _Alloc::getSingleton().allocate(size);

		if (!p)
		{
			throw std::bad_alloc();
		}

		return p;
	}

    static void* operator new[] (size_t size)
	{
		if (!size)
		{
			size = 1;
		}

		void* p = _Alloc::getSingleton().allocate(size);

		if (!p)
		{
			throw std::bad_alloc();
		}

		return p;
	}

#endif  // _DEBUG

    static void operator delete (void* p, size_t size)
	{
		if (p)
		{
			_Alloc::getSingleton().deallocate(p, size);
		}
	}

    static void operator delete[] (void *p, size_t size)
	{
		if (p)
		{
			_Alloc::getSingleton().deallocate(p, size);
		}
	}
};

#ifndef RfNew
#ifdef _DEBUG
#define RfNew	new(__FILE__, __LINE__)
#else
#define RfNew	new
#endif  // _DEBUG
#endif  // RfNew

#endif  // __Utils_Object_MemObject_H__
