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
#include "Thread/Coroutine.h"

#define N	10000

void producer()
{
	for (int i = 0; i < N; ++i)
	{
		Coroutine::yield<void>(i);
	}
}

void filter(CoroutinePtr co)
{
	int x = 0;
	
	for (int i = co->resume<int>(); co->status() != Coroutine::eDEAD; i = co->resume<int>())
	{
		CPPUNIT_ASSERT_EQUAL(x, i);
		Coroutine::yield<void>(x++);
	}
}

void consumer(CoroutinePtr co)
{
	int x = 0;
	
	for (int i = co->resume<int>(); co->status() != Coroutine::eDEAD; i = co->resume<int>())
	{
		CPPUNIT_ASSERT_EQUAL(x++, i);
	}
}

class CoroutineTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(CoroutineTest);
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
#ifndef __APPLE__
		consumer(RfNew Coroutine(boost::bind(filter, RfNew Coroutine(producer))));
#endif  // !__APPLE__
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(CoroutineTest);
