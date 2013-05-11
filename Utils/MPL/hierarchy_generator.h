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

#ifndef __Utils_MPL_hierarchy_generator_H__
#define __Utils_MPL_hierarchy_generator_H__

#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>

template <class _it0, class _it1, template <class> class _unit>
class scatter_hierarchy_impl
	: public _unit<typename boost::mpl::deref<_it0>::type>
	, public scatter_hierarchy_impl<typename boost::mpl::next<_it0>::type, _it1, _unit>
{
};

template <class _it, template <class> class _unit>
class scatter_hierarchy_impl<_it, _it, _unit>
{
};

template <class _seq, template <class> class _unit>
class scatter_hierarchy
	: public scatter_hierarchy_impl<
		typename boost::mpl::begin<_seq>::type,
		typename boost::mpl::end<_seq>::type,
		_unit
	>
{
};

template <class _it0, class _it1, template <class, class> class _unit, class _root>
class linear_hierarchy_impl
	: public _unit<
		typename boost::mpl::deref<_it0>::type,
		linear_hierarchy_impl<typename boost::mpl::next<_it0>::type, _it1, _unit, _root>
	>
{
};

template <class _it, template <class, class> class _unit, class _root>
class linear_hierarchy_impl<_it, _it, _unit, _root> : public _root
{
};

class linear_hierarchy_default_root
{
};

template <class _seq, template <class, class> class _unit, class _root = linear_hierarchy_default_root>
class linear_hierarchy
	: public linear_hierarchy_impl<
		typename boost::mpl::begin<_seq>::type,
		typename boost::mpl::end<_seq>::type,
		_unit,
		_root
	>
{
};

#endif  // __Utils_MPL_hierarchy_generator_H__
