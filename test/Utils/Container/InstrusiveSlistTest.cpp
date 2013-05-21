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
#include <algorithm>
#include "Container/instrusive_slist.h"

struct Mock : public instrusive_slist_node<Mock>
{
	size_t value;
};

class InstrusiveSlistTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(InstrusiveSlistTest);
	CPPUNIT_TEST(test);
	CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp()
	{
		for (size_t i = 0; i < sizeof(mMocks) / sizeof(mMocks[0]); ++i)
		{
			mMocks[i].value = i;
			mMocks[i].next() = 0;
		}
	}

	virtual void tearDown()
	{
	}

private:
	static bool predicate(const Mock& mock)
	{
		return mock.value < 8;
	}

	void test()
	{
		instrusive_slist<Mock> l;

		CPPUNIT_ASSERT(l.empty());
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), l.size());

		std::copy(mMocks, mMocks + 10, std::front_inserter(l));

		CPPUNIT_ASSERT(!l.empty());
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(10), l.size());
		
		size_t idx = 9;

		for (instrusive_slist<Mock>::iterator i = l.begin(); i != l.end(); ++i)
		{
			CPPUNIT_ASSERT_EQUAL(mMocks[idx--].value, i->value);
		}

		l.push_front(mMocks[10]);
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(11), l.size());
		CPPUNIT_ASSERT_EQUAL(mMocks[10].value, l.front().value);

		instrusive_slist<Mock>::iterator it = l.begin();

		std::advance(it, 3);
		l.insert(it, mMocks[11]);
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(12), l.size());
		CPPUNIT_ASSERT_EQUAL(it->value, mMocks[11].next()->value);
		
		it = l.begin();
		std::advance(it, 3);
		l.insert_after(it, mMocks[12]);
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(13), l.size());
		CPPUNIT_ASSERT_EQUAL(mMocks[12].value, it->next()->value);

		it = l.begin();
		std::advance(it, 3);
		l.erase_after(it);
		l.erase(it);
		l.pop_front();
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(10), l.size());

		idx = 9;
		for (instrusive_slist<Mock>::iterator i = l.begin(); i != l.end(); ++i)
		{
			CPPUNIT_ASSERT_EQUAL(mMocks[idx--].value, i->value);
		}

		l.remove(mMocks[5]);
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(9), l.size());
		CPPUNIT_ASSERT_EQUAL(mMocks[4].value, mMocks[6].next()->value);

		l.remove_after(mMocks[6]);
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(8), l.size());
		CPPUNIT_ASSERT_EQUAL(mMocks[3].value, mMocks[6].next()->value);

		it = l.begin();
		std::advance(it, 3);
		
		instrusive_slist<Mock>::iterator it0 = it;

		std::advance(it, 3);
		l.erase(it0, it);
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(5), l.size());

		l.remove_if(&InstrusiveSlistTest::predicate);
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), l.size());
		for (instrusive_slist<Mock>::iterator i = l.begin(); i != l.end(); ++i)
		{
			CPPUNIT_ASSERT(i->value >= 8);
		}

		l.clear();
		CPPUNIT_ASSERT(l.empty());
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), l.size());
	}

private:
	Mock mMocks[15];
};

CPPUNIT_TEST_SUITE_REGISTRATION(InstrusiveSlistTest);
