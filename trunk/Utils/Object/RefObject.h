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

template <
	class _alloc = Allocator,
	class _counter = long
>
class RefObject
	: public MemObject<_alloc>
	, private boost::noncopyable
{
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
		++mRefCount;
	}

    void decRefCount()
	{
		if (--mRefCount == 0)
		{
			delete this;
		}
	}

    const _counter& getRefCount() const
	{
		return mRefCount;
	}

private:
	_counter mRefCount;
};

#endif  // __Utils_Object_RefObject_H__
