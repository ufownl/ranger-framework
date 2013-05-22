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
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/at.hpp>
#include "MPL/hierarchy_generator.h"
#include "MPL/dummy.h"

class HierarchyGeneratorTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(HierarchyGeneratorTest);
	CPPUNIT_TEST(testScatter);
	CPPUNIT_TEST(testLinear);
	CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp()
	{
	}

	virtual void tearDown()
	{
	}

private:
	typedef boost::mpl::range_c<int, 0, 5> seq;

	template <class T>
	struct scatter_unit : public T
	{
		virtual ~scatter_unit() {}
		virtual void test_impl(dummy<T>) const = 0;
	};

	typedef scatter_hierarchy<seq, scatter_unit> scatter;

	void testScatter()
	{
		CPPUNIT_ASSERT((boost::is_base_of<boost::mpl::at_c<seq, 0>::type, scatter>::value));
		CPPUNIT_ASSERT((boost::is_base_of<boost::mpl::at_c<seq, 1>::type, scatter>::value));
		CPPUNIT_ASSERT((boost::is_base_of<boost::mpl::at_c<seq, 2>::type, scatter>::value));
		CPPUNIT_ASSERT((boost::is_base_of<boost::mpl::at_c<seq, 3>::type, scatter>::value));
		CPPUNIT_ASSERT((boost::is_base_of<boost::mpl::at_c<seq, 4>::type, scatter>::value));
	}

	struct linear_root : public scatter
	{
		template <class T>
		void test() const
		{
			const scatter_unit<T>* p = this;
			p->test_impl(dummy<T>());
		}
	};

	template <class T, class _base>
	struct linear_unit : public _base
	{
		virtual void test_impl(dummy<T>) const
		{
			CPPUNIT_ASSERT(dynamic_cast<const linear_root*>(this) == this);
		}
	};

	typedef linear_hierarchy<seq, linear_unit, linear_root> linear;

	void testLinear()
	{
		linear l;

		l.test<boost::mpl::at_c<seq, 0>::type>();
		l.test<boost::mpl::at_c<seq, 1>::type>();
		l.test<boost::mpl::at_c<seq, 2>::type>();
		l.test<boost::mpl::at_c<seq, 3>::type>();
		l.test<boost::mpl::at_c<seq, 4>::type>();
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(HierarchyGeneratorTest);
