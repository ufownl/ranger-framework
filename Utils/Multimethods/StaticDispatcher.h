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

#ifndef __Utils_Multimethods_StaticDispatcher_H__
#define __Utils_Multimethods_StaticDispatcher_H__

#include <boost/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/sort.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/index_of.hpp>

template <class T>
struct is_symmetric : boost::mpl::false_
{
};

template <
	class _executor,
	class _lhs_base,
	class _lhs_seq,
	class _lhs_it0,
	class _lhs_it1,
	class _rhs_base,
	class _rhs_seq,
	class _rhs_it0,
	class _rhs_it1,
	class _result
>
struct StaticDispatcherImpl
{
	template <class _swap, class _lhs, class _rhs>
	struct InvocationTraits
	{
		static _result dispatch(_lhs& lhs, _rhs& rhs, _executor& exec)
		{
			return exec(lhs, rhs);
		}
	};

	template <class _lhs, class _rhs>
	struct InvocationTraits<boost::mpl::true_, _lhs, _rhs>
	{
		static _result dispatch(_lhs& lhs, _rhs& rhs, _executor& exec)
		{
			return exec(rhs, lhs);
		}
	};

	static _result dispatch(_lhs_base& lhs, _rhs_base& rhs, _executor exec)
	{
		typedef typename boost::mpl::deref<_lhs_it0>::type front;

		front* p = dynamic_cast<front*>(&lhs);

		if (p == &lhs)
		{
			return StaticDispatcherImpl<
				_executor,
				_lhs_base,
				_lhs_seq,
				_lhs_it0,
				_lhs_it1,
				_rhs_base,
				_rhs_seq,
				_rhs_it0,
				_rhs_it1,
				_result
			>::dispatch_rhs(*p, rhs, exec);
		}
		else
		{
			return StaticDispatcherImpl<
				_executor,
				_lhs_base,
				_lhs_seq,
				typename boost::mpl::next<_lhs_it0>::type,
				_lhs_it1,
				_rhs_base,
				_rhs_seq,
				_rhs_it0,
				_rhs_it1,
				_result
			>::dispatch(lhs, rhs, exec);
		}
	}

	template <class T>
	static _result dispatch_rhs(T& lhs, _rhs_base& rhs, _executor exec)
	{
		typedef typename boost::mpl::deref<_rhs_it0>::type front;

		front* p = dynamic_cast<front*>(&rhs);

		if (p == &rhs)
		{
			return InvocationTraits<
				typename boost::mpl::and_<
					typename is_symmetric<_executor>::type,
					typename boost::mpl::greater<
						typename boost::mpl::index_of<_lhs_seq, T>::type,
						typename boost::mpl::index_of<_rhs_seq, front>::type
					>::type
				>::type,
				T,
				front
			>::dispatch(lhs, *p, exec);
		}
		else
		{
			return StaticDispatcherImpl<
				_executor,
				_lhs_base,
				_lhs_seq,
				_lhs_it0,
				_lhs_it1,
				_rhs_base,
				_rhs_seq,
				typename boost::mpl::next<_rhs_it0>::type,
				_rhs_it1,
				_result
			>::dispatch_rhs(lhs, rhs, exec);
		}
	}
};

template <
	class _executor,
	class _lhs_base,
	class _lhs_seq,
	class _lhs_it,
	class _rhs_base,
	class _rhs_seq,
	class _rhs_it0,
	class _rhs_it1,
	class _result
>
struct StaticDispatcherImpl<_executor, _lhs_base, _lhs_seq, _lhs_it, _lhs_it, _rhs_base, _rhs_seq, _rhs_it0, _rhs_it1, _result>
{
	static _result dispatch(_lhs_base& lhs, _rhs_base& rhs, _executor exec)
	{
		return exec(lhs, rhs);
	}
};

template <
	class _executor,
	class _lhs_base,
	class _lhs_seq,
	class _lhs_it0,
	class _lhs_it1,
	class _rhs_base,
	class _rhs_seq,
	class _rhs_it,
	class _result
>
struct StaticDispatcherImpl<_executor, _lhs_base, _lhs_seq, _lhs_it0, _lhs_it1, _rhs_base, _rhs_seq, _rhs_it, _rhs_it, _result>
{
	static _result dispatch_rhs(_lhs_base& lhs, _rhs_base& rhs, _executor exec)
	{
		return exec(lhs, rhs);
	}
};

template <
	class _lhs_base,
	class _lhs_seq,
	class _rhs_base = _lhs_base,
	class _rhs_seq = _lhs_seq,
	class _result = void
>
struct StaticDispatcher
{
	template <class _executor>
	static _result dispatch(_lhs_base& lhs, _rhs_base& rhs, _executor exec)
	{
		typedef typename boost::mpl::sort<
			_lhs_seq,
			boost::is_base_of<
				boost::mpl::_2,
				boost::mpl::_1
			>
		>::type lhs_sorted_seq;

		typedef typename boost::mpl::sort<
			_rhs_seq,
			boost::is_base_of<
				boost::mpl::_2,
				boost::mpl::_1
			>
		>::type rhs_sorted_seq;

		return StaticDispatcherImpl<
			_executor,
			_lhs_base,
			_lhs_seq,
			typename boost::mpl::begin<lhs_sorted_seq>::type,
			typename boost::mpl::end<lhs_sorted_seq>::type,
			_rhs_base,
			_rhs_seq,
			typename boost::mpl::begin<rhs_sorted_seq>::type,
			typename boost::mpl::end<rhs_sorted_seq>::type,
			_result
		>::dispatch(lhs, rhs, exec);
	}
};

#endif  // __Utils_Multimethods_StaticDispatcher_H__
