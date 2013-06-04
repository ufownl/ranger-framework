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
#include "Object/TypeInfo.h"

class TypeInfoTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TypeInfoTest);
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
	struct A
	{
	};

	struct B
	{
	};

	void test()
	{
		A a;
		B b;
		TypeInfo ai(typeid(a));
		TypeInfo bi(typeid(b));

		CPPUNIT_ASSERT(ai == typeid(a));
		CPPUNIT_ASSERT(typeid(a) == ai);
		CPPUNIT_ASSERT(bi == typeid(b));
		CPPUNIT_ASSERT(typeid(b) == bi);
		CPPUNIT_ASSERT(ai != bi);
		CPPUNIT_ASSERT(typeid(a) != bi);
		CPPUNIT_ASSERT(ai != typeid(b));
		CPPUNIT_ASSERT_EQUAL(typeid(a).before(typeid(b)), ai < bi);
		CPPUNIT_ASSERT_EQUAL(typeid(b).before(typeid(a)), bi < ai);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(TypeInfoTest);
