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
#include <boost/array.hpp>
#include "Container/round_robin_queue.h"

#define N	10000

class RoundRobinQueueTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(RoundRobinQueueTest);
	CPPUNIT_TEST(testVector);
	CPPUNIT_TEST(testArray);
	CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp()
	{
	}

	virtual void tearDown()
	{
	}

private:
	void testVector()
	{
		round_robin_queue<int> q(N);

		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(N), q.max_size());
		
		CPPUNIT_ASSERT(q.empty());
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), q.size());

		for (int i = 0; i < N * 2 / 3; ++i)
		{
			q.push(i);
		}

		CPPUNIT_ASSERT(!q.empty());
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(N * 2 / 3), q.size());
		CPPUNIT_ASSERT_EQUAL(0, q.front());
		CPPUNIT_ASSERT_EQUAL(N * 2 / 3 - 1, q.back());
		
		for (int i = 0; !q.empty(); ++i)
		{
			CPPUNIT_ASSERT_EQUAL(i, q.front());
			q.pop();
		}
		
		CPPUNIT_ASSERT(q.empty());
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), q.size());

		for (int i = 0; i < N + 100; ++i)
		{
			q.push(i);
		}

		CPPUNIT_ASSERT(!q.empty());
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(N), q.size());
		CPPUNIT_ASSERT_EQUAL(0, q.front());
		CPPUNIT_ASSERT_EQUAL(N - 1, q.back());

		for (int i = 0; !q.empty(); ++i)
		{
			CPPUNIT_ASSERT_EQUAL(i, q.front());
			q.pop();
		}
		
		CPPUNIT_ASSERT(q.empty());
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), q.size());
	}

	void testArray()
	{
		round_robin_queue<int, boost::array<int, N> > q;

		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(N), q.max_size());
		
		CPPUNIT_ASSERT(q.empty());
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), q.size());

		for (int i = 0; i < N * 2 / 3; ++i)
		{
			q.push(i);
		}

		CPPUNIT_ASSERT(!q.empty());
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(N * 2 / 3), q.size());
		CPPUNIT_ASSERT_EQUAL(0, q.front());
		CPPUNIT_ASSERT_EQUAL(N * 2 / 3 - 1, q.back());
		
		for (int i = 0; !q.empty(); ++i)
		{
			CPPUNIT_ASSERT_EQUAL(i, q.front());
			q.pop();
		}
		
		CPPUNIT_ASSERT(q.empty());
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), q.size());

		for (int i = 0; i < N + 100; ++i)
		{
			q.push(i);
		}

		CPPUNIT_ASSERT(!q.empty());
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(N), q.size());
		CPPUNIT_ASSERT_EQUAL(0, q.front());
		CPPUNIT_ASSERT_EQUAL(N - 1, q.back());

		for (int i = 0; !q.empty(); ++i)
		{
			CPPUNIT_ASSERT_EQUAL(i, q.front());
			q.pop();
		}
		
		CPPUNIT_ASSERT(q.empty());
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), q.size());
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(RoundRobinQueueTest);
