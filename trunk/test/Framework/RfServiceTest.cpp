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
#include "RfService.h"

class RfServiceTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(RfServiceTest);
	CPPUNIT_TEST(test);
	CPPUNIT_TEST_SUITE_END();

	class TestService : public RfService
	{
	public:
		TestService()
			: mInitRet(false)
			, mTickRet(false)
		{
		}

		virtual ~TestService()
		{
		}

		void setInitRet(bool ret)
		{
			mInitRet = ret;
		}

		void setTickRet(bool ret)
		{
			mTickRet = ret;
		}

	protected:
		virtual bool onInitialize()
		{
			if (!RfService::onInitialize())
			{
				return false;
			}

			return mInitRet;
		}

		virtual bool onTick(long escape)
		{
			if (!RfService::onTick(escape))
			{
				return false;
			}

			return mTickRet;
		}
		
	private:
		bool mInitRet;
		bool mTickRet;
	};

public:
	virtual void setUp()
	{
		mService = RfNew TestService;
	}

	virtual void tearDown()
	{
		mService->shutdown();
		mService = 0;
	}

private:
	void test()
	{
		CPPUNIT_ASSERT(!mService->tick());

		mService->setTickRet(true);
		CPPUNIT_ASSERT(!mService->tick());

		mService->setInitRet(true);
		CPPUNIT_ASSERT(mService->tick());

		mService->setInitRet(false);
		CPPUNIT_ASSERT(mService->tick());

		mService->setTickRet(false);
		CPPUNIT_ASSERT(!mService->tick());

		mService->shutdown();
		mService->setInitRet(false);
		mService->setTickRet(false);
		CPPUNIT_ASSERT(!mService->tick());

		mService->setInitRet(true);
		mService->setTickRet(true);
		CPPUNIT_ASSERT(mService->tick());
	}

private:
	SmartPointer<TestService> mService;
};

CPPUNIT_TEST_SUITE_REGISTRATION(RfServiceTest);
