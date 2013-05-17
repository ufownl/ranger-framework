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

template <class _alloc = Allocator>
class MemObject
{
public:
#ifdef _DEBUG
    static void* operator new (size_t size, const char* file, long line)
#else
    static void* operator new (size_t size)
#endif  // _DEBUG
	{
		if (!size)
		{
			size = 1;
		}

		while (true)
		{
#ifdef _DEBUG
			void* p = _alloc::getSingleton().allocate(size, file, line);
#else
			void* p = _alloc::getSingleton().allocate(size);
#endif // _DEBUG

			if (p)
			{
				return p;
			}

			std::new_handler handler = std::set_new_handler(0);
			std::set_new_handler(handler);

			if (handler)
			{
				handler();
			}
			else
			{
				throw std::bad_alloc();
			}
		}
	}

#ifdef _DEBUG
    static void* operator new[] (size_t size, const char* file, long line)
#else
    static void* operator new[] (size_t size)
#endif  // _DEBUG
	{
		if (!size)
		{
			size = 1;
		}

		while (true)
		{
#ifdef _DEBUG
			void* p = _alloc::getSingleton().allocate(size, file, line);
#else
			void* p = _alloc::getSingleton().allocate(size);
#endif // _DEBUG

			if (p)
			{
				return p;
			}

			std::new_handler handler = std::set_new_handler(0);
			std::set_new_handler(handler);

			if (handler)
			{
				handler();
			}
			else
			{
				throw std::bad_alloc();
			}
		}
	}

#ifdef _DEBUG
    static void operator delete (void* p, const char*, long)
	{
		if (p)
		{
			_alloc::getSingleton().deallocate(p);
		}
	}

    static void operator delete[] (void* p, const char*, long)
	{
		if (p)
		{
			_alloc::getSingleton().deallocate(p);
		}
	}
#endif  // _DEBUG

    static void operator delete (void* p, size_t size)
	{
		if (p)
		{
			_alloc::getSingleton().deallocate(p, size);
		}
	}

    static void operator delete[] (void* p, size_t size)
	{
		if (p)
		{
			_alloc::getSingleton().deallocate(p, size);
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
