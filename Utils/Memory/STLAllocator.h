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

#ifndef __Utils_Memory_STLAllocator_H__
#define __Utils_Memory_STLAllocator_H__

#include "Memory/Allocator.h"
#include <new>

template <class T>
struct STLAllocatorBase
{
	typedef T value_type;
};

template <class T>
struct STLAllocatorBase<const T>
{
	typedef T value_type;
};

template <class T, class _alloc = Allocator>
class STLAllocator : public STLAllocatorBase<T>
{
public:
	typedef typename STLAllocatorBase<T>::value_type value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef const value_type* const_pointer;
	typedef const value_type& const_reference;

	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	template <class U>
	struct rebind
	{
		typedef STLAllocator<U, _alloc> other;
	};

	STLAllocator()
	{
	}

	template <class U, class A>
	STLAllocator(const STLAllocator<U, A>&)
	{
	}

	template <class U, class A>
	STLAllocator<T>& operator = (const STLAllocator<U, A>&)
	{
		return *this;
	}

	pointer address(reference val) const
	{
		return &val;
	}

	const_pointer address(const_reference val) const
	{
		return &val;
	}

	void deallocate(pointer p, size_type count)
	{
		_alloc::deallocate(p, count * sizeof(T));
	}

	pointer allocate(size_type count, const void* hint = 0)
	{
		pointer p = 0;
		
#ifdef _DEBUG
		p = static_cast<pointer>(_alloc::allocate(count * sizeof(T), __FILE__, __LINE__));
#else
		p = static_cast<pointer>(_alloc::allocate(count * sizeof(T)));
#endif  // _DEBUG

		if (!p)
		{
			throw std::bad_alloc();
		}

		return p;
	}

	void construct(pointer p, const T &val)
	{
		::new(p) T(val);
	}

	void destroy(pointer p)
	{
		p->~T();
	}

	size_type max_size() const
	{
		return _alloc::max_size();
	}
};

template <class T, class U, class A>
bool operator == (const STLAllocator<T, A>&, const STLAllocator<U, A>&)
{
	return true;
}

template <class T, class U, class A>
bool operator != (const STLAllocator<T, A>&, const STLAllocator<U, A>&)
{
	return false;
}

template <class T, class A, class _other>
bool operator == (const STLAllocator<T, A>&, const _other&)
{
	return false;
}

template <class T, class A, class _other>
bool operator != (const STLAllocator<T, A>&, const _other&)
{
	return true;
}

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
template <class T>
struct stl_alloc
{
	typedef STLAllocator<T, TCMallocAllocator> type;
};
#else
template <class T>
struct stl_alloc
{
	typedef STLAllocator<T> type;
};
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

#endif  // __Utils_Memory_STLAllocator_H__
