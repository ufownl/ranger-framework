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

#ifndef __Utils_Object_RefObject_H__
#define __Utils_Object_RefObject_H__

#include "Object/MemObject.h"
#include "Thread/ThreadPolicy.h"
#include "Thread/ScopedLock.h"

template <
	class _alloc = Allocator,
	class _storage = unsigned int,
	template <class> class _thread_policy = ObjectLevelLockable
>
class RefObject
	: public MemObject<_alloc>
	, public _thread_policy<RefObject<_alloc, _storage, _thread_policy> >
{
public:
	typedef _thread_policy<RefObject<_alloc, _storage, _thread_policy> > ThreadPolicy;

public:
    RefObject()
		: mRefCount(0)
	{
	}

    virtual ~RefObject()
	{
	}

    void incRefCount()
	{
		typename ThreadPolicy::Lock l(*this);
		ScopedLock<typename ThreadPolicy::Lock> sl(l);
		++mRefCount;
	}

    void decRefCount()
	{
		typename ThreadPolicy::Lock l(*this);

		l.lock();
		if (--mRefCount == 0)
		{
			l.unlock();
			delete this;
			return;
		}
		l.unlock();
	}

    _storage getRefCount()
	{
		return mRefCount;
	}

private:
    RefObject(const RefObject&);
    RefObject& operator = (const RefObject&);

private:
	typename ThreadPolicy::template Data<_storage>::type mRefCount;
};

#endif  // __Utils_Object_RefObject_H__
