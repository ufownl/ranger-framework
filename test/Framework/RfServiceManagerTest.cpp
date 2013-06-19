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
#include "RfServiceManager.h"

class RfServiceManagerTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(RfServiceManagerTest);
	CPPUNIT_TEST(test);
	CPPUNIT_TEST_SUITE_END();

	template <size_t N>
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
		mManager = RfNew RfServiceManager;
	}

	virtual void tearDown()
	{
		mManager = 0;
	}

private:
	void test()
	{
		mManager->append(RfNew TestService<0>);
		mManager->append(RfNew TestService<1>);
		mManager->append(RfNew TestService<2>);

		CPPUNIT_ASSERT(mManager->find<TestService<0> >() != mManager->nil());
		CPPUNIT_ASSERT(mManager->find<TestService<1> >() != mManager->nil());
		CPPUNIT_ASSERT(mManager->find<TestService<2> >() != mManager->nil());

		CPPUNIT_ASSERT(mManager->get<TestService<0> >());
		CPPUNIT_ASSERT(mManager->get<TestService<1> >());
		CPPUNIT_ASSERT(mManager->get<TestService<2> >());

		mManager->remove<TestService<2> >();

		CPPUNIT_ASSERT(mManager->find<TestService<0> >() != mManager->nil());
		CPPUNIT_ASSERT(mManager->find<TestService<1> >() != mManager->nil());
		CPPUNIT_ASSERT(mManager->find<TestService<2> >() == mManager->nil());

		CPPUNIT_ASSERT(mManager->get<TestService<0> >());
		CPPUNIT_ASSERT(mManager->get<TestService<1> >());
		CPPUNIT_ASSERT(!mManager->get<TestService<2> >());

		CPPUNIT_ASSERT(!mManager->tick());
		mManager->get<TestService<0> >()->setInitRet(true);
		mManager->get<TestService<0> >()->setTickRet(true);
		CPPUNIT_ASSERT(!mManager->tick());
		mManager->get<TestService<1> >()->setInitRet(true);
		mManager->get<TestService<1> >()->setTickRet(true);
		CPPUNIT_ASSERT(mManager->tick());
	}

private:
	RfServiceManagerPtr mManager;
};

CPPUNIT_TEST_SUITE_REGISTRATION(RfServiceManagerTest);
