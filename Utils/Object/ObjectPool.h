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

#ifndef __Utils_Object_ObjectPool_H__
#define __Utils_Object_ObjectPool_H__

#include "Thread/ThreadPolicy.h"
#include "Thread/ScopedLock.h"
#include "Container/instrusive_slist.h"
#include "Memory/std_tcmalloc_allocator.h"
#include <vector>
#include <algorithm>
#include <iterator>
#include <assert.h>

template <class T, template <class> class _thread_policy = ObjectLevelLockable>
class ObjectPool : public _thread_policy<ObjectPool<T, _thread_policy> >
{
public:
	typedef _thread_policy<ObjectPool<T, _thread_policy> > ThreadPolicy;

private:
	typedef void (T::*callback_t)();

public:
	ObjectPool(size_t size, callback_t alloc = 0, callback_t dealloc = 0)
		: mPool(size)
		, mOnAlloc(alloc)
		, mOnDealloc(dealloc)
	{
		std::copy(mPool.begin(), mPool.end(), std::front_inserter(mFree));
	}

	T* allocate()
	{
		typename ThreadPolicy::Lock l(*this);
		ScopedLock<typename ThreadPolicy::Lock> sl(l);

		if (mFree.empty())
		{
			return 0;
		}

		T* p = &mFree.front();
		mFree.pop_front();

		if (mOnAlloc)
		{
			l.unlock();
			(p->*mOnAlloc)();
			l.lock();
		}

		return p;
	}

	void deallocate(T* p)
	{
		typename ThreadPolicy::Lock l(*this);
		ScopedLock<typename ThreadPolicy::Lock> sl(l);

		assert(&mPool.front() <= p && p <= &mPool.back());
		assert(((char*)p - (char*)&mPool.front()) % sizeof(T) == 0);

		if (mOnDealloc)
		{
			l.unlock();
			(p->*mOnDealloc)();
			l.lock();
		}

		mFree.push_front(*p);
	}

	T* pool()
	{
		return &mPool.front();
	}

	size_t size()
	{
		return mPool.size();
	}

private:
	std::vector<T, std_alloc<T> > mPool;
	instrusive_slist<T> mFree;
	callback_t mOnAlloc;
	callback_t mOnDealloc;
};

#endif  // __Utils_Object_ObjectPool_H__
