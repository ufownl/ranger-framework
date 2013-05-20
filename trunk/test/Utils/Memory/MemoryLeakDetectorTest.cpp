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
#include "Memory/MemoryLeakDetector.h"
#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define Test_Alloc	TCMallocAllocator
#else
#include "Memory/Allocator.h"
#define Test_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

#define N	1000

class MemoryLeakDetectorTestTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(MemoryLeakDetectorTestTest);
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
#ifdef _DEBUG
		MemoryState state;

		MemoryLeakDetector::getSingleton().checkMemoryState(state);

		size_t init = state.size();
		void* p[N];

		for (size_t i = 0; i < N; ++i)
		{
			p[i] = Test_Alloc::allocate(1, __FILE__, __LINE__);
			MemoryLeakDetector::getSingleton().checkMemoryState(state);
			CPPUNIT_ASSERT_EQUAL(init + i + 1, state.size());
		}
		MemoryLeakDetector::getSingleton().checkMemoryState(state);
		CPPUNIT_ASSERT_EQUAL(init + N, state.size());

		size_t idx = 0;

		for (MemoryState::iterator i = state.begin(); i != state.end(); ++i)
		{
			if (idx >= init)
			{
				CPPUNIT_ASSERT_EQUAL(p[idx++ - init], i->addr);
			}
		}

		for (size_t i = 0; i < N; ++i)
		{
			Test_Alloc::deallocate(p[i]);
			MemoryLeakDetector::getSingleton().checkMemoryState(state);
			CPPUNIT_ASSERT_EQUAL(init + N - i - 1, state.size());
		}
		MemoryLeakDetector::getSingleton().checkMemoryState(state);
		CPPUNIT_ASSERT_EQUAL(init, state.size());
#endif  // _DEBUG
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(MemoryLeakDetectorTestTest);
