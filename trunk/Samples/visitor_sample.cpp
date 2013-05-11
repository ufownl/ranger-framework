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

#include "Object/Visitor.h"
#include <boost/mpl/vector.hpp>
#include <vector>
#include <stdio.h>

struct A;
struct B;
struct C;

typedef Visitor<boost::mpl::vector<A, B, C> > IMyVisitor;

struct Base
{
	VISITABLE_DECL_ABS(IMyVisitor)
};

struct A : Base
{
	VISITABLE_DECL(IMyVisitor)
};

struct B : Base
{
	VISITABLE_DECL(IMyVisitor)
};

struct C : Base
{
	VISITABLE_DECL(IMyVisitor)
};

VISITABLE_IMPL(A, IMyVisitor)
VISITABLE_IMPL(B, IMyVisitor)
VISITABLE_IMPL(C, IMyVisitor)

struct MyVisitor : IMyVisitor
{
	virtual void onVisit(A&)
	{
		puts("visit A");
	}

	virtual void onVisit(B&)
	{
		puts("visit B");
	}

	virtual void onVisit(C&)
	{
		puts("visit C");
	}
};

void visitor_sample()
{
	putchar('\n');
	puts(__FUNCTION__);
	putchar('\n');

	MyVisitor visitor;
	std::vector<Base*> v(3);

	v[0] = new A;
	v[1] = new B;
	v[2] = new C;

	for (std::vector<Base*>::iterator i = v.begin(); i != v.end(); ++i)
	{
		(*i)->accept(visitor);
	}

	for (std::vector<Base*>::iterator i = v.begin(); i != v.end(); ++i)
	{
		delete *i;
	}
}

int main()
{
	visitor_sample();
	return 0;
}
