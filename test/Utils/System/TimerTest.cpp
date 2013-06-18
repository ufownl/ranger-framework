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
#include "System/Timer.h"

class TimerTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TimerTest);
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
		unsigned int t = RfClock();
		RfSleep(1000);
		CPPUNIT_ASSERT(RfClock() - t >= 1000);

		t = RfClock();
		RfSleep(2000);
		CPPUNIT_ASSERT(RfClock() - t >= 2000);

		t = RfClock();
		RfSleep(3000);
		CPPUNIT_ASSERT(RfClock() - t >= 3000);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(TimerTest);
