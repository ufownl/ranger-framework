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
#include <boost/detail/atomic_count.hpp>
#include "Object/RefObject.h"

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define Object_Alloc	TCMallocAllocator
#else
#define Object_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class RefObjectTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(RefObjectTest);
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
	template <class _counter>
	struct Object : public RefObject<Object_Alloc, _counter>
	{
		Object()
		{
			++count;
		}

		~Object()
		{
			--count;
		}

		static long count;
	};

	template <class _counter>
	void test_impl()
	{
		Object<_counter>* obj = RfNew Object<_counter>;

		CPPUNIT_ASSERT_EQUAL(static_cast<long>(1), Object<_counter>::count);
		CPPUNIT_ASSERT_EQUAL(static_cast<long>(0), (long)obj->getRefCount());
		obj->incRefCount();
		CPPUNIT_ASSERT_EQUAL(static_cast<long>(1), (long)obj->getRefCount());
		obj->incRefCount();
		CPPUNIT_ASSERT_EQUAL(static_cast<long>(2), (long)obj->getRefCount());
		obj->decRefCount();
		CPPUNIT_ASSERT_EQUAL(static_cast<long>(1), (long)obj->getRefCount());
		obj->decRefCount();
		CPPUNIT_ASSERT_EQUAL(static_cast<long>(0), Object<_counter>::count);
	}

	void test()
	{
		test_impl<long>();
		test_impl<boost::detail::atomic_count>();
	}
};

template <class _counter>
long RefObjectTest::Object<_counter>::count = 0;

CPPUNIT_TEST_SUITE_REGISTRATION(RefObjectTest);
