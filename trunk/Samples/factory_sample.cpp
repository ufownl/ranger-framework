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

#include "Object/Factory.h"
#include "Object/AbstractFactory.h"
#include <boost/mpl/vector.hpp>
#include <typeinfo>
#include <stdio.h>

struct Base
{
	virtual ~Base() {}
};

struct A : Base
{
};

struct B : Base
{
};

struct C : B
{
};

struct D : B
{
};

Base* new_A()
{
	return new A;
}

Base* new_B()
{
	return new B;
}

Base* new_C()
{
	return new C;
}

Base* new_D()
{
	return new D;
}

typedef Factory<Base, int> MyFactory;

void factory_sample()
{
	putchar('\n');
	puts(__FUNCTION__);
	putchar('\n');

	MyFactory factory;

	factory.regist(0, new_A);
	factory.regist(1, new_B);
	factory.regist(2, new_C);
	factory.regist(3, new_D);

	for (int i = 0; i < 6; ++i)
	{
		Base* p = factory.create(i);

		if (p)
		{
			puts(typeid(*p).name());
			delete p;
		}
		else
		{
			puts("Class not registed.");
		}
	}
}

struct B0
{
	virtual ~B0() {}
};

struct D00 : B0
{
};

struct D01 : B0
{
};

struct B1
{
	virtual ~B1() {}
};

struct D10 : B1
{
};

struct D11 : B1
{
};

void abstract_factory_sample()
{
	putchar('\n');
	puts(__FUNCTION__);
	putchar('\n');

	typedef AbstractFactory<boost::mpl::vector<B0, B1> > IMyAbsFactory;
	typedef ConcreteFactory<IMyAbsFactory, boost::mpl::vector<D00, D10> > MyFactory0;
	typedef ConcreteFactory<IMyAbsFactory, boost::mpl::vector<D01, D11> > MyFactory1;

	IMyAbsFactory* factory0 = new MyFactory0;
	IMyAbsFactory* factory1 = new MyFactory1;
	B0* p0;
	B1* p1;

	p0 = factory0->create<B0>();
	puts(typeid(*p0).name());
	delete p0;
	p1 = factory0->create<B1>();
	puts(typeid(*p1).name());
	delete p1;
	p0 = factory1->create<B0>();
	puts(typeid(*p0).name());
	delete p0;
	p1 = factory1->create<B1>();
	puts(typeid(*p1).name());
	delete p1;

	delete factory0;
	delete factory1;
}

int main()
{
	factory_sample();
	abstract_factory_sample();
	return 0;
}
