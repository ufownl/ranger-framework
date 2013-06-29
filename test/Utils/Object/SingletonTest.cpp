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
#include "Object/Singleton.h"

namespace singleton_test
{

	struct Mock : public Singleton<Mock>
	{
	};

	static Mock gsMock;

}

namespace singleton_holder_test
{

	struct Mock
	{
	};

}

class SingletonTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(SingletonTest);
	CPPUNIT_TEST(testSingleton);
	CPPUNIT_TEST(testSingletonHolder);
	CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp()
	{
	}

	virtual void tearDown()
	{
	}

private:
	void testSingleton()
	{
		CPPUNIT_ASSERT_EQUAL(&singleton_test::Mock::getSingleton(), &singleton_test::Mock::getSingleton());
		CPPUNIT_ASSERT_EQUAL(&singleton_test::Mock::getSingleton(), singleton_test::Mock::getSingletonPtr());
		CPPUNIT_ASSERT_EQUAL(singleton_test::Mock::getSingletonPtr(), &singleton_test::Mock::getSingleton());
		CPPUNIT_ASSERT_EQUAL(singleton_test::Mock::getSingletonPtr(), singleton_test::Mock::getSingletonPtr());

		try
		{
			singleton_test::Mock m;
		}
		catch (const std::logic_error& e)
		{
			CPPUNIT_ASSERT_EQUAL(&singleton_test::gsMock, singleton_test::Mock::getSingletonPtr());
			return;
		}

		CPPUNIT_ASSERT(false);
	}

	void testSingletonHolder()
	{
		CPPUNIT_ASSERT_EQUAL(
			&SingletonHolder<singleton_holder_test::Mock>::instance(),
			&SingletonHolder<singleton_holder_test::Mock>::instance()
		);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(SingletonTest);
