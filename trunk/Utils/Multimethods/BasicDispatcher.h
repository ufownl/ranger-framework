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

#ifndef __Utils_Multimethods_BasicDispatcher_H__
#define __Utils_Multimethods_BasicDispatcher_H__

#include "Object/TypeInfo.h"
#include "Container/associate_vector.h"
#include "Memory/STLAllocator.h"

template <class _lhs_base, class _rhs_base, class _result, class _callback, class _error_handler>
class BasicDispatcher
{
private:
	typedef std::pair<TypeInfo, TypeInfo> key_t;
	typedef associate_vector<
		key_t,
		_callback,
		std::less<key_t>,
		typename stl_alloc<std::pair<key_t, _callback> >::type
	> map_t;

public:
	template <class _lhs, class _rhs>
	void regist(const _callback& fn)
	{
		key_t key(typeid(_lhs), typeid(_rhs));
		typename map_t::iterator it = mCallbacks.find(key);

		if (it == mCallbacks.end())
		{
			mCallbacks.insert(std::make_pair(key, fn));
		}
		else
		{
			it->second = fn;
		}
	}

	_result dispatch(_lhs_base& lhs, _rhs_base& rhs)
	{
		key_t key(typeid(lhs), typeid(rhs));
		typename map_t::iterator it = mCallbacks.find(key);

		if (it == mCallbacks.end())
		{
			return _error_handler::onError(lhs, rhs);
		}

		return (it->second)(lhs, rhs);
	}

private:
	map_t mCallbacks;
};

#endif  // __Utils_Multimethods_BasicDispatcher_H__
