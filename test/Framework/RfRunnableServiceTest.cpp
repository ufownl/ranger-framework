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
#include "RfRunnableService.h"

class RfRunnableServiceTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(RfRunnableServiceTest);
	CPPUNIT_TEST(test);
	CPPUNIT_TEST_SUITE_END();

	class TestService : public RfRunnableService
	{
	public:
		TestService()
			: RfRunnableService(1000)
			, mCount(0)
		{
		}

		virtual ~TestService()
		{
		}

	protected:
		bool onInitialize()
		{
			if (!RfRunnableService::onInitialize())
			{
				return false;
			}

			mCount = 0;

			return true;
		}

		bool onTick(long escape)
		{
			if (!RfRunnableService::onTick(escape))
			{
				return false;
			}

			CPPUNIT_ASSERT(escape >= (mCount++) * 1000);
			
			if (mCount >= 5)
			{
				stop();
			}

			return true;
		}

	private:
		int mCount;
	};

public:
	virtual void setUp()
	{
		mService = RfNew TestService;
	}

	virtual void tearDown()
	{
		mService = 0;
	}

private:
	void test()
	{
		unsigned int t = RfClock();
		mService->run();
		CPPUNIT_ASSERT(RfClock() - t >= 5000);
	}

private:
	SmartPointer<TestService> mService;
};

CPPUNIT_TEST_SUITE_REGISTRATION(RfRunnableServiceTest);
