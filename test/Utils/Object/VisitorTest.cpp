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
#include "Object/Visitor.h"

namespace visitor_test
{

	struct A;
	struct B;
	struct C;

	typedef Visitor<boost::mpl::vector<A, B, C>, int> IMyVisitor;

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
		virtual int onVisit(A&)
		{
			return 0;
		}

		virtual int onVisit(B&)
		{
			return 1;
		}

		virtual int onVisit(C&)
		{
			return 2;
		}
	};

}

class VisitorTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(VisitorTest);
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
	void test()
	{
		visitor_test::A a;
		visitor_test::B b;
		visitor_test::C c;
		visitor_test::Base* p[] = {&a, &b, &c};
		visitor_test::MyVisitor v;

		for (int i = 0; i < 3; ++i)
		{
			CPPUNIT_ASSERT_EQUAL(i, p[i]->accept(v));
		}
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(VisitorTest);
