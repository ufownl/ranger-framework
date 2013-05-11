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

#ifndef __Utils_MPL_bind_H__
#define __Utils_MPL_bind_H__

template <template <class, class> class _bin_t, class _arg>
struct bind1st
{
	template <class T>
	struct type : _bin_t<_arg, T>
	{
	};
};

template <template <class, class> class _bin_t, class _arg>
struct bind2nd
{
	template <class T>
	struct type : _bin_t<T, _arg>
	{
	};
};

#endif  // __Utils_MPL_bind_H__
