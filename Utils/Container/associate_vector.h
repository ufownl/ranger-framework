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

#ifndef __Utils_Container_associate_vector_H__
#define __Utils_Container_associate_vector_H__

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stddef.h>

template <
	class _key,
	class _val,
	class _comp = std::less<_key>,
	class _alloc = std::allocator<std::pair<_key, _val> >
>
class associate_vector
{
public:
	typedef associate_vector<_key, _val, _comp, _alloc> self;

	typedef std::pair<_key, _val> value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;

	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	typedef _key key_type;
	typedef _val mapped_type;
	typedef _comp key_compare;

private:
	typedef std::vector<value_type, _alloc> backend_t;

public:
	typedef typename backend_t::allocator_type allocator_type;

	typedef typename backend_t::iterator iterator;
	typedef typename backend_t::const_iterator const_iterator;
	typedef typename backend_t::reverse_iterator reverse_iterator;
	typedef typename backend_t::const_reverse_iterator const_reverse_iterator;

	class value_compare : public std::binary_function<value_type, value_type, bool>
	{
	public:
		value_compare(const _comp& comp)
			: mComp(comp)
		{
		}

		bool operator () (const value_type& a, const value_type& b)
		{
			return mComp(a.first, b.first);
		}

	protected:
		_comp mComp;
	};

public:
	explicit associate_vector(const _comp& comp = _comp(), const _alloc& alloc = _alloc())
		: mBackend(alloc)
		, mComp(comp)
	{
	}

	explicit associate_vector(size_type size, const _comp& comp = _comp(), const _alloc& alloc = _alloc())
		: mBackend(alloc)
		, mComp(comp)
	{
		mBackend.reserve(size);
	}

	associate_vector(const self& rhs)
		: mBackend(rhs.mBackend)
		, mComp(rhs.mComp)
	{
	}

	self& operator = (const self& rhs)
	{
		mBackend = rhs.mBackend;
		mComp = rhs.mComp;
		return *this;
	}

	allocator_type get_allocator() const
	{
		return mBackend.get_allocator();
	}

	iterator begin()
	{
		return mBackend.begin();
	}

	const_iterator begin() const
	{
		return mBackend.begin();
	}

	iterator end()
	{
		return mBackend.end();
	}

	const_iterator end() const
	{
		return mBackend.end();
	}
	
	reverse_iterator rbegin()
	{
		return mBackend.rbegin();
	}

	const_reverse_iterator rbegin() const
	{
		return mBackend.rbegin();
	}

	reverse_iterator rend()
	{
		return mBackend.rend();
	}

	const_reverse_iterator rend() const
	{
		return mBackend.rend();
	}

	bool empty() const
	{
		return mBackend.empty();
	}

	size_type size() const
	{
		return mBackend.size();
	}

	size_type max_size() const
	{
		return mBackend.max_size();
	}

	void reserve(size_type size)
	{
		mBackend.reserve(size);
	}

	size_type capacity() const
	{
		return mBackend.capacity();
	}

	void clear()
	{
		mBackend.clear();
	}

	iterator insert(const value_type& val)
	{
		return mBackend.insert(std::upper_bound(mBackend.begin(), mBackend.end(), val, value_comp()), val);
	}

	template <class _it>
	void insert(_it first, _it last)
	{
		for ( ; first != last; ++first)
		{
			insert(*first);
		}
	}

	void erase(iterator pos)
	{
		mBackend.erase(pos);
	}

	void erase(iterator first, iterator last)
	{
		mBackend.erase(first, last);
	}

	size_type erase(const key_type& key)
	{
		std::pair<iterator, iterator> range
			= std::equal_range(mBackend.begin(), mBackend.end(), value_type(key, mapped_type()), value_comp());
		size_type size = std::distance(range.first, range.second);

		mBackend.erase(range.first, range.second);
		return size;
	}

	void swap(self& rhs)
	{
		mBackend.swap(rhs.mBackend);
		std::swap(mComp, rhs.mComp);
	}

	size_type count(const key_type& key)
	{
		std::pair<iterator, iterator> range
			= std::equal_range(mBackend.begin(), mBackend.end(), value_type(key, mapped_type()), value_comp());
		return std::distance(range.first, range.second);
	}

	iterator find(const key_type& key)
	{
		std::pair<iterator, iterator> range
			= std::equal_range(mBackend.begin(), mBackend.end(), value_type(key, mapped_type()), value_comp());
		return range.first == range.second ? mBackend.end() : range.first;
	}

	const_iterator find(const key_type& key) const
	{
		std::pair<const_iterator, const_iterator> range
			= std::equal_range(mBackend.begin(), mBackend.end(), value_type(key, mapped_type()), value_comp());
		return range.first == range.second ? mBackend.end() : range.first;
	}

	std::pair<iterator, iterator> equal_range(const key_type& key)
	{
		return std::equal_range(mBackend.begin(), mBackend.end(), value_type(key, mapped_type()), value_comp());
	}

	std::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
	{
		return std::equal_range(mBackend.begin(), mBackend.end(), value_type(key, mapped_type()), value_comp());
	}

	iterator lower_bound(const key_type& key)
	{
		return std::lower_bound(mBackend.begin(), mBackend.end(), value_type(key, mapped_type()), value_comp());
	}

	const_iterator lower_bound(const key_type& key) const
	{
		return std::lower_bound(mBackend.begin(), mBackend.end(), value_type(key, mapped_type()), value_comp());
	}

	iterator upper_bound(const key_type& key)
	{
		return std::upper_bound(mBackend.begin(), mBackend.end(), value_type(key, mapped_type()), value_comp());
	}

	const_iterator upper_bound(const key_type& key) const
	{
		return std::upper_bound(mBackend.begin(), mBackend.end(), value_type(key, mapped_type()), value_comp());
	}

	key_compare key_comp() const
	{
		return mComp;
	}

	value_compare value_comp() const
	{
		return value_compare(mComp);
	}

private:
	backend_t mBackend;
	key_compare mComp;
};

namespace std
{

	template <class _key, class _val, class _comp, class _alloc>
	void swap(associate_vector<_key, _val, _comp, _alloc>& av0, associate_vector<_key, _val, _comp, _alloc>& av1)
	{
		av0.swap(av1);
	}

}

#endif  // __Utils_Container_associate_vector_H__
