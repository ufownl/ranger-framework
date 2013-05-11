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

#ifndef __Utils_Object_AbstractFactory_H__
#define __Utils_Object_AbstractFactory_H__

#include "MPL/dummy.h"
#include "MPL/hierarchy_generator.h"
#include <boost/mpl/pop_back.hpp>
#include <boost/mpl/back.hpp>

template <class T>
struct AfUnit
{
	virtual ~AfUnit()
	{
	}

	virtual T* create(dummy<T>) = 0;
};

template <class _seq>
struct AbstractFactory : public scatter_hierarchy<_seq, AfUnit>
{
	typedef _seq ProductSeq;

	template <class T>
	T* create()
	{
		AfUnit<T>* p = this;
		return p->create(dummy<T>());
	}
};

template <class T, class _base>
struct OpNewCfUnit : public _base
{
	typedef typename _base::ProductSeq BaseProductSeq;
	typedef typename boost::mpl::pop_back<BaseProductSeq>::type ProductSeq;
	typedef typename boost::mpl::back<BaseProductSeq>::type Product;

	virtual T* create(dummy<Product>)
	{
		return new T;
	}
};

#ifndef RfNew
#ifdef _DEBUG
#define RfNew	new(__FILE__, __LINE__)
#else
#define RfNew	new
#endif  // _DEBUG
#endif  // RfNew

template <class T, class _base>
struct OpRfNewCfUnit : public _base
{
	typedef typename _base::ProductSeq BaseProductSeq;
	typedef typename boost::mpl::pop_back<BaseProductSeq>::type ProductSeq;
	typedef typename boost::mpl::back<BaseProductSeq>::type Product;

	virtual T* create(dummy<Product>)
	{
		return RfNew T;
	}
};

template <
	class _abs_factory,
	class _seq,
	template <class, class> class _creator = OpNewCfUnit
>
struct ConcreteFactory : public linear_hierarchy<_seq, _creator, _abs_factory>
{
	typedef typename _abs_factory::ProductSeq ProductSeq;
	typedef _seq ConcreteProductSeq;
};

#endif  // __Utils_Object_AbstractFactory_H__
