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
#include "Container/instrusive_list.h"

struct Mock : public instrusive_list_node<Mock>
{
	size_t value;
};

bool predicate(const Mock& mock)
{
	return mock.value < 8;
}

class InstrusiveListTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(InstrusiveListTest);
	CPPUNIT_TEST(test);
	CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp()
	{
		for (size_t i = 0; i < sizeof(mMocks) / sizeof(mMocks[0]); ++i)
		{
			mMocks[i].value = i;
			mMocks[i].next() = 0;
			mMocks[i].prev() = 0;
		}
	}

	virtual void tearDown()
	{
	}

private:
	void test()
	{
		instrusive_list<Mock> l;

		CPPUNIT_ASSERT(l.empty());
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), l.size());

		std::copy(mMocks, mMocks + 10, std::back_inserter(l));

		CPPUNIT_ASSERT(!l.empty());
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(10), l.size());
		
		size_t idx = 0;

		for (instrusive_list<Mock>::iterator i = l.begin(); i != l.end(); ++i)
		{
			CPPUNIT_ASSERT_EQUAL(mMocks[idx++].value, i->value);
		}

		l.push_front(mMocks[10]);
		l.push_back(mMocks[11]);
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(12), l.size());
		CPPUNIT_ASSERT_EQUAL(mMocks[10].value, l.front().value);
		CPPUNIT_ASSERT_EQUAL(mMocks[11].value, l.back().value);

		instrusive_list<Mock>::iterator it = l.begin();

		std::advance(it, 3);
		l.insert(it, mMocks[12]);
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(13), l.size());
		CPPUNIT_ASSERT_EQUAL(mMocks[12].value, it->prev()->value);
		CPPUNIT_ASSERT_EQUAL(it->value, mMocks[12].next()->value);

		it = l.begin();
		std::advance(it, 3);
		l.erase(it);
		l.pop_front();
		l.pop_back();
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(10), l.size());

		idx = 0;
		for (instrusive_list<Mock>::iterator i = l.begin(); i != l.end(); ++i)
		{
			CPPUNIT_ASSERT_EQUAL(mMocks[idx++].value, i->value);
		}

		l.remove(mMocks[5]);
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(9), l.size());
		CPPUNIT_ASSERT_EQUAL(mMocks[6].value, mMocks[4].next()->value);

		it = l.begin();
		std::advance(it, 3);
		
		instrusive_list<Mock>::iterator it0 = it;

		std::advance(it, 3);
		l.erase(it0, it);
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(6), l.size());

		l.remove_if(predicate);
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), l.size());
		for (instrusive_list<Mock>::iterator i = l.begin(); i != l.end(); ++i)
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

CPPUNIT_TEST_SUITE_REGISTRATION(InstrusiveListTest);
