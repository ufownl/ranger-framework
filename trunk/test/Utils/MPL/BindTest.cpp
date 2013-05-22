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
#include "MPL/bind.h"

class BindTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(BindTest);
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
	template <class _arg0, class _arg1>
	struct dummy
	{
	};

	template <class _arg0, class _arg1>
	void test_impl()
	{
		CPPUNIT_ASSERT((boost::is_same<dummy<_arg0, _arg1>, typename bind<dummy, _arg0>::template first<_arg1>::type >::value));
		CPPUNIT_ASSERT((boost::is_base_of<dummy<_arg0, _arg1>, typename bind<dummy, _arg0>::template first<_arg1> >::value));

		CPPUNIT_ASSERT((boost::is_same<dummy<_arg1, _arg0>, typename bind<dummy, _arg0>::template second<_arg1>::type >::value));
		CPPUNIT_ASSERT((boost::is_base_of<dummy<_arg1, _arg0>, typename bind<dummy, _arg0>::template second<_arg1> >::value));
	}

	void test()
	{
		test_impl<int, bool>();
		test_impl<int, char>();
		test_impl<int, int>();
		test_impl<int, float>();
		test_impl<int, double>();
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(BindTest);
