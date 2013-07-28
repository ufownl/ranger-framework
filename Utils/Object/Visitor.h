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

#ifndef __Utils_Object_Visitor_H__
#define __Utils_Object_Visitor_H__

#include "MPL/hierarchy_generator.h"
#include "MPL/bind.h"

template <class T, class R>
struct VisitorUnit
{
	virtual R onVisit(T&) = 0;
};

template <class _seq, class R = void>
struct Visitor : public scatter_hierarchy<_seq, bind<VisitorUnit, R>::template second>
{
	typedef R Result;

	template <class T>
	R visit(T& host)
	{
		VisitorUnit<T, R>* p = this;
		return p->onVisit(host);
	}
};

#define VISITABLE_DECL_ABS(_visitor)	virtual _visitor::Result accept(_visitor&) = 0;
#define VISITABLE_DECL(_visitor)		virtual _visitor::Result accept(_visitor&);
#define VISITABLE_DECL_NONVIRTUAL(_visitor)		_visitor::Result accept(_visitor&);
#define VISITABLE_IMPL(_host, _visitor)	\
	_visitor::Result _host::accept(_visitor& v) { return v.visit(*this); }

#endif  // __Utils_Object_Visitor_H__
