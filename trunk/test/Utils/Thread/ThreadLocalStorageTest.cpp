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
#if !defined(_WIN32) && !defined(_WIN64)
#include "Thread/ThreadLocalStorage.h"
#endif  // !_WIN32 && !_WIN64

class ThreadLocalStorageTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ThreadLocalStorageTest);
	CPPUNIT_TEST(test);
	CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp()
	{
		mVal0 = 2013;
		mVal1 = 2014;
	}

	virtual void tearDown()
	{
	}

private:
	void test()
	{
#if !defined(_WIN32) && !defined(_WIN64)
		ThreadLocalStorage<int> tls0;
		ThreadLocalStorage<int> tls1(&mVal1);

		CPPUNIT_ASSERT(!tls0);
		CPPUNIT_ASSERT(tls1);

		tls0 = &mVal0;

		CPPUNIT_ASSERT_EQUAL(mVal0, *tls0);
		CPPUNIT_ASSERT_EQUAL(mVal1, *tls1);
		CPPUNIT_ASSERT_EQUAL(mVal0 - mVal1, *tls0 - *tls1);
		CPPUNIT_ASSERT_EQUAL(++(*tls0), *tls1);
		CPPUNIT_ASSERT_EQUAL(*tls0, *tls1);
		CPPUNIT_ASSERT_EQUAL(mVal0, mVal1);
#endif  // !_WIN32 && !_WIN64
	}

private:
	int mVal0;
	int mVal1;
};

CPPUNIT_TEST_SUITE_REGISTRATION(ThreadLocalStorageTest);
