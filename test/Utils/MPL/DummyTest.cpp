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
#include <boost/type_traits.hpp>
#include "MPL/dummy.h"

class DummyTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(DummyTest);
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
	template <class T>
	void test_impl()
	{
		CPPUNIT_ASSERT((boost::is_same<T, typename dummy<T>::type>::value));
	}

	void test()
	{
		test_impl<bool>();
		test_impl<char>();
		test_impl<int>();
		test_impl<float>();
		test_impl<double>();
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(DummyTest);
