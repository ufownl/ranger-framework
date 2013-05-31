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
#include "Object/RefObject.h"

class RefObjectTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(RefObjectTest);
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
	struct Object : public RefObject<>
	{
		Object()
		{
			++count;
		}

		~Object()
		{
			--count;
		}

		static size_t count;
	};

	void test()
	{
		Object* obj = RfNew Object;

		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), Object::count);
		CPPUNIT_ASSERT_EQUAL(static_cast<unsigned int>(0), obj->getRefCount());
		obj->incRefCount();
		CPPUNIT_ASSERT_EQUAL(static_cast<unsigned int>(1), obj->getRefCount());
		obj->incRefCount();
		CPPUNIT_ASSERT_EQUAL(static_cast<unsigned int>(2), obj->getRefCount());
		obj->decRefCount();
		CPPUNIT_ASSERT_EQUAL(static_cast<unsigned int>(1), obj->getRefCount());
		obj->decRefCount();
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), Object::count);
	}
};

size_t RefObjectTest::Object::count = 0;

CPPUNIT_TEST_SUITE_REGISTRATION(RefObjectTest);
