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

#include "cppunit/extensions/HelperMacros.h"
#include "Memory/STLAllocator.h"

struct Mock
{
	Mock(int a = 0)
		: value(a)
	{
	}

	~Mock()
	{
		++value;
	}

	int value;
};

class STLAllocatorTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(STLAllocatorTest);
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
		Mock* p = mAlloc.allocate(1);

		mAlloc.construct(p, Mock());
		CPPUNIT_ASSERT_EQUAL(0, p->value);
		mAlloc.destroy(p);
		CPPUNIT_ASSERT_EQUAL(0 + 1, p->value);
		mAlloc.construct(p, 2013);
		CPPUNIT_ASSERT_EQUAL(2013, p->value);
		mAlloc.destroy(p);
		CPPUNIT_ASSERT_EQUAL(2013 + 1, p->value);

		mAlloc.deallocate(p, 1);
	}

private:
	stl_alloc<Mock>::type mAlloc;
};

CPPUNIT_TEST_SUITE_REGISTRATION(STLAllocatorTest);
