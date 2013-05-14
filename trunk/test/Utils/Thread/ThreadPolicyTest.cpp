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
#include "Thread/ThreadPolicy.h"
#include <boost/type_traits.hpp>

template <class T>
struct ClassLevel : public ClassLevelLockable<ClassLevel<T> >
{
	typedef typename ClassLevelLockable<ClassLevel<T> >::template Data<T>::type type;
};

template <class T>
struct ObjectLevel : public ObjectLevelLockable<ObjectLevel<T> >
{
	typedef typename ObjectLevelLockable<ObjectLevel<T> >::template Data<T>::type type;
};

template <class T>
struct Single : public SingleThread<Single<T> >
{
	typedef typename SingleThread<Single<T> >::template Data<T>::type type;
};

class ThreadPolicyTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ThreadPolicyTest);
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
		CPPUNIT_ASSERT((boost::is_same<ClassLevel<int>::type, volatile int>::value));
		CPPUNIT_ASSERT((boost::is_same<ObjectLevel<int>::type, volatile int>::value));
		CPPUNIT_ASSERT((boost::is_same<Single<int>::type, int>::value));
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(ThreadPolicyTest);
