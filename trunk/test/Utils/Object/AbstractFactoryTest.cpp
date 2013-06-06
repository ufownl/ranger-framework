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

#include <cppunit/extensions/HelperMacros.h>
#include <boost/mpl/vector.hpp>
#include "Object/AbstractFactory.h"

class AbstractFactoryTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(AbstractFactoryTest);
	CPPUNIT_TEST(test);
	CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp()
	{
	}

	virtual void tearDown()
	{
	}

private:
	struct B0
	{
		virtual ~B0()
		{
		}
		
		virtual int id() const = 0;
	};

	struct D00 : B0
	{
		virtual int id() const
		{
			return class_id();
		}

		static int class_id()
		{
			return 0x00;
		}
	};

	struct D01 : B0
	{
		virtual int id() const
		{
			return class_id();
		}

		static int class_id()
		{
			return 0x01;
		}
	};

	struct B1
	{
		virtual ~B1()
		{
		}

		virtual int id() const = 0;
	};

	struct D10 : B1
	{
		virtual int id() const
		{
			return class_id();
		}

		static int class_id()
		{
			return 0x10;
		}
	};

	struct D11 : B1
	{
		virtual int id() const
		{
			return class_id();
		}

		static int class_id()
		{
			return 0x11;
		}
	};

	typedef AbstractFactory<boost::mpl::vector<B0, B1> > IMyAbsFactory;
	typedef ConcreteFactory<IMyAbsFactory, boost::mpl::vector<D00, D10> > MyFactory0;
	typedef ConcreteFactory<IMyAbsFactory, boost::mpl::vector<D01, D11> > MyFactory1;

	void test()
	{
		MyFactory0 f0;
		MyFactory1 f1;

		{
			IMyAbsFactory* f = &f0;
			B0* p = f->create<B0>();
			CPPUNIT_ASSERT_EQUAL(0x00, p->id());
		}

		{
			IMyAbsFactory* f = &f1;
			B0* p = f->create<B0>();
			CPPUNIT_ASSERT_EQUAL(0x01, p->id());
		}

		{
			IMyAbsFactory* f = &f0;
			B1* p = f->create<B1>();
			CPPUNIT_ASSERT_EQUAL(0x10, p->id());
		}

		{
			IMyAbsFactory* f = &f1;
			B1* p = f->create<B1>();
			CPPUNIT_ASSERT_EQUAL(0x11, p->id());
		}
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(AbstractFactoryTest);
