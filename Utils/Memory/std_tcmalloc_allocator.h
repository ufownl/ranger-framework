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

#ifndef __Utils_Memory_std_tcmalloc_allocator_H__
#define __Utils_Memory_std_tcmalloc_allocator_H__

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)

#include <tcmalloc.h>

namespace std
{

	template<class T>
	struct allocator_base
	{
		typedef T value_type;
	};

	template<class T>
	struct allocator_base<const T>
	{
		typedef T value_type;
	};

	template<class T>
	class tcmalloc_allocator : public allocator_base<T>
	{
	public:
		typedef typename allocator_base<T>::value_type value_type;
		typedef value_type* pointer;
		typedef value_type& reference;
		typedef const value_type* const_pointer;
		typedef const value_type& const_reference;

		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		template<class _Other>
		struct rebind
		{
			typedef tcmalloc_allocator<_Other> other;
		};

		pointer address(reference val) const
		{
			return (&val);
		}

		const_pointer address(const_reference val) const
		{
			return (&val);
		}

		tcmalloc_allocator()
		{
		}

		tcmalloc_allocator(const tcmalloc_allocator<T>&)
		{
		}

		template<class _Other>
		tcmalloc_allocator(const tcmalloc_allocator<_Other>&)
		{
		}

		template<class _Other>
		tcmalloc_allocator<T>& operator=(const tcmalloc_allocator<_Other>&)
		{
			return *this;
		}

		void deallocate(pointer ptr, size_type)
		{
			tc_free(ptr);
		}

		pointer allocate(size_type count)
		{
			return (pointer)tc_malloc(count * sizeof(T));
		}

		pointer allocate(size_type count, const void*)
		{
			return allocate(count);
		}

		void construct(pointer ptr, const T &val)
		{
			::new(ptr) T(val);
		}

		void destroy(pointer ptr)
		{
			ptr->~T();
		}

		size_type max_size() const
		{
			size_type count = (size_type)(-1) / sizeof (T);
			return (0 < count ? count : 1);
		}
	};

	template <typename T, typename _Other>
	bool operator == (tcmalloc_allocator<T>&, tcmalloc_allocator<_Other>&)
	{
		return true;
	}

	template <typename T, typename _Other>
	bool operator != (tcmalloc_allocator<T>&, tcmalloc_allocator<_Other>&)
	{
		return false;
	}

}

#define std_alloc	std::tcmalloc_allocator

#else

#include <memory>
#define std_alloc	std::allocator

#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

#endif  // __Utils_Memory_std_tcmalloc_allocator_H__
