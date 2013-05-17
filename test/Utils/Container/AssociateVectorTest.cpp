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
#include "Container/associate_vector.h"

class AssociateVectorTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(AssociateVectorTest);
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
		typedef associate_vector<int, int> test_type;
		test_type v(10);

		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(10), v.capacity());

		v.insert(std::make_pair(0, 10));
		v.insert(std::make_pair(1, 9));
		v.insert(std::make_pair(2, 8));
		v.insert(std::make_pair(3, 7));
		v.insert(std::make_pair(2, 8));
		v.insert(std::make_pair(1, 9));
		v.insert(std::make_pair(0, 10));

		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(7), v.size());

		for (test_type::iterator i = v.begin() + 1; i != v.end(); ++i)
		{
			CPPUNIT_ASSERT((i - 1)->first <= i->first);
		}

		std::pair<test_type::iterator, test_type::iterator> range = v.equal_range(1);
		for (test_type::iterator i = range.first; i != range.second; ++i)
		{
			CPPUNIT_ASSERT_EQUAL(1, i->first);
		}

		test_type::iterator it = v.lower_bound(2);
		for (test_type::iterator i = v.begin(); i != it; ++i)
		{
			CPPUNIT_ASSERT(i->first < 2);
		}

		it = v.upper_bound(1);
		for (test_type::iterator i = it; i != v.end(); ++i)
		{
			CPPUNIT_ASSERT(i->first > 1);
		}

		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), v.count(0));
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), v.count(1));
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), v.count(2));
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), v.count(3));

		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), v.erase(2));
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(5), v.size());

		CPPUNIT_ASSERT(v.find(0) != v.end());
		CPPUNIT_ASSERT(v.find(1) != v.end());
		CPPUNIT_ASSERT(v.find(2) == v.end());
		CPPUNIT_ASSERT(v.find(3) != v.end());

		v.clear();
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), v.size());
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(AssociateVectorTest);
