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

#ifndef __Utils_Multimethods_DynamicDispatcher_H__
#define __Utils_Multimethods_DynamicDispatcher_H__

#include "Multimethods/BasicDispatcher.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <stdexcept>

template <class _from, class _to>
struct DynamicCaster
{
	static _to& cast(_from& obj)
	{
		return dynamic_cast<_to&>(obj);
	}
};

template <class _from, class _to>
struct StaticCaster
{
	static _to& cast(_from& obj)
	{
		return static_cast<_to&>(obj);
	}
};

template <class _lhs_base, class _rhs_base, class _result>
struct ThrowExceptionHandler
{
	static _result onError(_lhs_base&, _rhs_base&)
	{
		throw std::invalid_argument("Function not found.");
	}
};

template <class _lhs_base, class _rhs_base, class _result>
struct ReturnZeroHandler
{
	static _result onError(_lhs_base&, _rhs_base&)
	{
		return _result(0);
	}
};

template <
	class _lhs_base,
	class _rhs_base = _lhs_base,
	class _result = void,
	template <class, class> class _caster = DynamicCaster,
	template <class, class, class, class, class> class _backend = BasicDispatcher,
	template <class, class, class> class _error_handler = ThrowExceptionHandler
>
class FnDispatcher
{
public:
	template <
		class _lhs,
		class _rhs,
		_result (*_callback)(_lhs&, _rhs&),
		bool _symmetric
	>
	void regist()
	{
		struct Local
		{
			static _result dispatch(_lhs_base& lhs, _rhs_base& rhs)
			{
				return _callback(
					_caster<_lhs_base, _lhs>::cast(lhs),
					_caster<_rhs_base, _rhs>::cast(rhs)
				);
			}

			static _result dispatch_swap(_rhs_base& rhs, _lhs_base& lhs)
			{
				return dispatch(lhs, rhs);
			}
		};

		mBackend.regist<_lhs, _rhs>(&Local::dispatch);

		if (_symmetric)
		{
			mBackend.regist<_rhs, _lhs>(&Local::dispatch_swap);
		}
	}

	_result dispatch(_lhs_base& lhs, _rhs_base& rhs)
	{
		return mBackend.dispatch(lhs, rhs);
	}

private:
	_backend<
		_lhs_base,
		_rhs_base,
		_result,
		_result(*)(_lhs_base&, _rhs_base&),
		_error_handler<_lhs_base, _rhs_base, _result>
	> mBackend;
};

template <
	class _lhs_base,
	class _rhs_base = _lhs_base,
	class _result = void,
	template <class, class> class _caster = DynamicCaster,
	template <class, class, class, class, class> class _backend = BasicDispatcher,
	template <class, class, class> class _error_handler = ThrowExceptionHandler
>
class FunctorDispatcher
{
public:
	template <class _lhs, class _rhs, bool _symmetric, class _callback>
	void regist(const _callback& fun)
	{
		struct Local
		{
			static _result dispatch(_callback fun, _lhs_base& lhs, _rhs_base& rhs)
			{
				return fun(
					_caster<_lhs_base, _lhs>::cast(lhs),
					_caster<_rhs_base, _rhs>::cast(rhs)
				);
			}

			static _result dispatch_swap(_callback fun, _rhs_base& rhs, _lhs_base& lhs)
			{
				return dispatch(fun, lhs, rhs);
			}
		};

		mBackend.regist<_lhs, _rhs>(boost::bind(&Local::dispatch, fun, _1, _2));

		if (_symmetric)
		{
			mBackend.regist<_rhs, _lhs>(boost::bind(&Local::dispatch_swap, fun, _1, _2));
		}
	}

	_result dispatch(_lhs_base& lhs, _rhs_base& rhs)
	{
		return mBackend.dispatch(lhs, rhs);
	}

private:
	_backend<
		_lhs_base,
		_rhs_base,
		_result,
		boost::function<_result(_lhs_base&, _rhs_base&)>,
		_error_handler<_lhs_base, _rhs_base, _result>
	> mBackend;
};

#endif  // __Utils_Multimethods_DynamicDispatcher_H__
