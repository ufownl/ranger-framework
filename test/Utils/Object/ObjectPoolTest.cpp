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
#include "Object/ObjectPool.h"

class ObjectPoolTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ObjectPoolTest);
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
	class node_t : public instrusive_slist_node<node_t>
	{
	public:
		node_t()
			: mIsAllocated(false)
		{
		}

		void onAllocate()
		{
			mIsAllocated = true;
		}

		void onDeallocate()
		{
			mIsAllocated = false;
		}

		bool isAllocated() const
		{
			return mIsAllocated;
		}

	private:
		bool mIsAllocated;
	};

	void test()
	{
		ObjectPool<node_t> pool(10, &node_t::onAllocate, &node_t::onDeallocate);
		node_t* p[15];

		for (size_t i = 0; i < 15; ++i)
		{
			p[i] = pool.allocate();

			if (p[i])
			{
				CPPUNIT_ASSERT(p[i]->isAllocated());
				CPPUNIT_ASSERT(p[i] >= pool.pool());
				CPPUNIT_ASSERT(p[i] <= pool.pool() + pool.size());
				CPPUNIT_ASSERT(((char*)p[i] - (char*)pool.pool()) % sizeof(node_t) == 0);
			}
			else
			{
				CPPUNIT_ASSERT(i >= 10);
			}
		}

		for (size_t i = 0; i < 15; ++i)
		{
			if (p[i])
			{
				pool.deallocate(p[i]);
				CPPUNIT_ASSERT(!p[i]->isAllocated());
			}
		}
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(ObjectPoolTest);
