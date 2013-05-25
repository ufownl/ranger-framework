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

#ifndef __Utils_Container_round_robin_queue_H__
#define __Utils_Container_round_robin_queue_H__

#include <vector>
#include <algorithm>
#include <stddef.h>

template <class T, class _container = std::vector<T> >
class round_robin_queue
{
public:
	typedef _container container_type;
	typedef typename _container::value_type value_type;
	typedef typename _container::size_type size_type;
	typedef typename _container::reference reference;
	typedef typename _container::const_reference const_reference;

public:
	round_robin_queue()
		: mFront(0)
		, mBack(0)
		, mSize(0)
	{
	}

	explicit round_robin_queue(size_type size)
		: mContainer(size)
		, mFront(0)
		, mBack(0)
		, mSize(0)
	{
	}

	template <class _alloc>
	round_robin_queue(size_type size, const _alloc& alloc)
		: mContainer(size, T(), alloc)
		, mFront(0)
		, mBack(0)
		, mSize(0)
	{
	}
	
	reference front()
	{
		return mContainer[mFront];
	}

	const_reference front() const
	{
		return mContainer[mFront];
	}

	reference back()
	{
		ptrdiff_t idx = mBack - 1;
		return mContainer[idx < 0 ? mContainer.size() + idx : idx];
	}

	const_reference back() const
	{
		ptrdiff_t idx = mBack - 1;
		return mContainer[idx < 0 ? mContainer.size() + idx : idx];
	}

	bool empty() const
	{
		return mSize == 0;
	}

	size_type size() const
	{
		return mSize;
	}

	size_type max_size() const
	{
		return mContainer.size();
	}

	void push(const T& val)
	{
		if (mSize >= max_size())
		{
			return;
		}
		
		mContainer[mBack] = val;
		++mSize;

		if (size_type(++mBack) >= mContainer.size())
		{
			mBack -= mContainer.size();
		}
	}

	void pop()
	{
		if (empty())
		{
			return;
		}

		--mSize;

		if (size_type(++mFront) >= mContainer.size())
		{
			mFront -= mContainer.size();
		}
	}

	void swap(round_robin_queue<T, _container>& rhs)
	{
		using std::swap;
		swap(mContainer, rhs.mContainer);
		swap(mFront, rhs.mFront);
		swap(mBack, rhs.mBack);
		swap(mSize, rhs.mSize);
	}

private:
	container_type mContainer;
	ptrdiff_t mFront;
	ptrdiff_t mBack;
	size_type mSize;
};

template <class T, class _container>
void swap(round_robin_queue<T, _container>& lhs, round_robin_queue<T, _container>& rhs)
{
	lhs.swap(rhs);
}

#endif  // __Utils_Container_round_robin_queue_H__
