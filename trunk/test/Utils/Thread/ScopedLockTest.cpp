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
#include "Thread/ScopedLock.h"

struct Lock
{
	Lock()
		: isLock(false)
	{
	}

	void lock()
	{
		isLock = true;
	}

	void unlock()
	{
		isLock = false;
	}

	bool isLock;
};

class ScopedLockTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ScopedLockTest);
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
		Lock lock;

		CPPUNIT_ASSERT(!lock.isLock);
		{
			ScopedLock<Lock> sl(lock);
			CPPUNIT_ASSERT(lock.isLock);
		}
		CPPUNIT_ASSERT(!lock.isLock);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(ScopedLockTest);
