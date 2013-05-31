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
#include "Object/SmartPointer.h"
#include "Object/RefObject.h"

class SmartPointerTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(SmartPointerTest);
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

	typedef SmartPointer<Object> ObjectPtr;

	void test()
	{
		ObjectPtr p0 = RfNew Object;

		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), Object::count);
		CPPUNIT_ASSERT_EQUAL(static_cast<unsigned int>(1), p0->getRefCount());

		ObjectPtr p1 = p0;

		CPPUNIT_ASSERT_EQUAL(p1, p0);
		CPPUNIT_ASSERT_EQUAL(p1.data(), p0.data());
		CPPUNIT_ASSERT_EQUAL(static_cast<unsigned int>(2), p0->getRefCount());

		{
			ObjectPtr p2 = p0;

			CPPUNIT_ASSERT_EQUAL(p2, p0);
			CPPUNIT_ASSERT_EQUAL(p2.data(), p0.data());
			CPPUNIT_ASSERT_EQUAL(static_cast<unsigned int>(3), p0->getRefCount());
		}

		CPPUNIT_ASSERT_EQUAL(static_cast<unsigned int>(2), p0->getRefCount());

		ObjectPtr p3 = RfNew Object;

		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), Object::count);
		CPPUNIT_ASSERT_EQUAL(static_cast<unsigned int>(1), p3->getRefCount());
		CPPUNIT_ASSERT(p0 != p3);
		CPPUNIT_ASSERT(p0.data() != p3.data());
		CPPUNIT_ASSERT_EQUAL(p0 < p3, p0.data() < p3.data());
		CPPUNIT_ASSERT_EQUAL(p0 <= p3, p0.data() <= p3.data());
		CPPUNIT_ASSERT_EQUAL(p0 > p3, p0.data() > p3.data());
		CPPUNIT_ASSERT_EQUAL(p0 >= p3, p0.data() >= p3.data());

		p3 = 0;
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), Object::count);
		
		p1 = 0;
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), Object::count);
		CPPUNIT_ASSERT_EQUAL(static_cast<unsigned int>(1), p0->getRefCount());

		p0 = 0;
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), Object::count);
	}
};

size_t SmartPointerTest::Object::count = 0;

CPPUNIT_TEST_SUITE_REGISTRATION(SmartPointerTest);
