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
#include <boost/mpl/vector.hpp>
#include "Multimethods/StaticDispatcher.h"
#include "Multimethods/DynamicDispatcher.h"
#include "Multimethods/FastDispatcher.h"

namespace multimethods_test
{

	struct Base
	{
		INDEXABLE_DECL()	// for fast dispatcher.

		virtual ~Base()
		{
		}

		virtual unsigned int id() const = 0;
	};

	INDEXABLE_IMPL(Base)	// for fast dispatcher.

	struct A : Base
	{
		INDEXABLE_DECL()	// for fast dispatcher.

		virtual unsigned int id() const
		{
			return class_id();
		}

		static unsigned int class_id()
		{
			return 0x01;
		}
	};

	INDEXABLE_IMPL(A)	// for fast dispatcher.

	struct B : Base
	{
		INDEXABLE_DECL()	// for fast dispatcher.

		virtual unsigned int id() const
		{
			return class_id();
		}

		static unsigned int class_id()
		{
			return 0x02;
		}
	};

	INDEXABLE_IMPL(B)	// for fast dispatcher.

	struct C : B
	{
		INDEXABLE_DECL()	// for fast dispatcher.

		virtual unsigned int id() const
		{
			return class_id();
		}

		static unsigned int class_id()
		{
			return 0x03;
		}
	};

	INDEXABLE_IMPL(C)	// for fast dispatcher.

	struct D : B
	{
		INDEXABLE_DECL()	// for fast dispatcher.

		virtual unsigned int id() const
		{
			return class_id();
		}

		static unsigned int class_id()
		{
			return 0x04;
		}
	};

	INDEXABLE_IMPL(D)	// for fast dispatcher.

	struct Executor
	{
		unsigned int operator () (A&, A&)
		{
			return (A::class_id() << 4) | A::class_id();
		}
		
		unsigned int operator () (A&, B&)
		{
			return (A::class_id() << 4) | B::class_id();
		}

		unsigned int operator () (A&, C&)
		{
			return (A::class_id() << 4) | C::class_id();
		}

		unsigned int operator () (A&, D&)
		{
			return (A::class_id() << 4) | D::class_id();
		}

		unsigned int operator () (B&, B&)
		{
			return (B::class_id() << 4) | B::class_id();
		}

		unsigned int operator () (B&, C&)
		{
			return (B::class_id() << 4) | C::class_id();
		}

		unsigned int operator () (B&, D&)
		{
			return (B::class_id() << 4) | D::class_id();
		}

		unsigned int operator () (C&, C&)
		{
			return (C::class_id() << 4) | C::class_id();
		}

		unsigned int operator () (C&, D&)
		{
			return (C::class_id() << 4) | D::class_id();
		}

		unsigned int operator () (D&, D&)
		{
			return (D::class_id() << 4) | D::class_id();
		}

		unsigned int operator () (Base&, Base&)
		{
			return 0;
		}
	};

	struct ExecutorSymmetric : Executor
	{
	};

	unsigned int ExecAA(A&, A&)
	{
		return (A::class_id() << 4) | A::class_id();
	}

	unsigned int ExecAB(A&, B&)
	{
		return (A::class_id() << 4) | B::class_id();
	}

	unsigned int ExecAC(A&, C&)
	{
		return (A::class_id() << 4) | C::class_id();
	}

	unsigned int ExecAD(A&, D&)
	{
		return (A::class_id() << 4) | D::class_id();
	}

	unsigned int ExecBB(B&, B&)
	{
		return (B::class_id() << 4) | B::class_id();
	}

	unsigned int ExecBC(B&, C&)
	{
		return (B::class_id() << 4) | C::class_id();
	}

	unsigned int ExecBD(B&, D&)
	{
		return (B::class_id() << 4) | D::class_id();
	}

	unsigned int ExecCC(C&, C&)
	{
		return (C::class_id() << 4) | C::class_id();
	}

	unsigned int ExecCD(C&, D&)
	{
		return (C::class_id() << 4) | D::class_id();
	}

	unsigned int ExecDD(D&, D&)
	{
		return (D::class_id() << 4) | D::class_id();
	}

}

template <>
struct is_symmetric<multimethods_test::ExecutorSymmetric> : boost::mpl::true_
{
};

#define FN_DISPATCHER(backend)	\
	using namespace multimethods_test;	\
	typedef FnDispatcher<Base, Base, unsigned int, StaticCaster, backend, ReturnZeroHandler> MyFnDispatcher;	\
	MyFnDispatcher disp;	\
	disp.regist<A, A, ExecAA, false>();	\
	disp.regist<A, B, ExecAB, false>();	\
	disp.regist<A, C, ExecAC, false>();	\
	disp.regist<A, D, ExecAD, false>();	\
	disp.regist<B, B, ExecBB, false>();	\
	disp.regist<B, C, ExecBC, false>();	\
	disp.regist<B, D, ExecBD, false>();	\
	disp.regist<C, C, ExecCC, false>();	\
	disp.regist<C, D, ExecCD, false>();	\
	disp.regist<D, D, ExecDD, false>();	\
	MyFnDispatcher symm;	\
	symm.regist<A, A, ExecAA, true>();	\
	symm.regist<A, B, ExecAB, true>();	\
	symm.regist<A, C, ExecAC, true>();	\
	symm.regist<A, D, ExecAD, true>();	\
	symm.regist<B, B, ExecBB, true>();	\
	symm.regist<B, C, ExecBC, true>();	\
	symm.regist<B, D, ExecBD, true>();	\
	symm.regist<C, C, ExecCC, true>();	\
	symm.regist<C, D, ExecCD, true>();	\
	symm.regist<D, D, ExecDD, true>();	\
	A a;	\
	B b;	\
	C c;	\
	D d;	\
	Base* p[4] = {&a, &b, &c, &d};	\
	for (size_t i = 0; i < 4; ++i)	\
	{	\
		for (size_t j = i; j < 4; ++j)	\
		{	\
			CPPUNIT_ASSERT_EQUAL((p[i]->id() << 4) | p[j]->id(), disp.dispatch(*p[i], *p[j]));	\
			CPPUNIT_ASSERT_EQUAL((p[i]->id() << 4) | p[j]->id(), symm.dispatch(*p[i], *p[j]));	\
		}	\
	}	\
	for (size_t i = 0; i < 4; ++i)	\
	{	\
		for (size_t j = 0; j < i; ++j)	\
		{	\
			CPPUNIT_ASSERT_EQUAL(static_cast<unsigned int>(0), disp.dispatch(*p[i], *p[j]));	\
			CPPUNIT_ASSERT_EQUAL((p[j]->id() << 4) | p[i]->id(), symm.dispatch(*p[i], *p[j]));	\
		}	\
	}

#define FUNCTOR_DISPATCHER(backend)	\
	using namespace multimethods_test;	\
	typedef FunctorDispatcher<Base, Base, unsigned int, StaticCaster, backend, ReturnZeroHandler> MyFunctorDispatcher;	\
	Executor exec;	\
	MyFunctorDispatcher disp;	\
	disp.regist<A, A, false>(exec);	\
	disp.regist<A, B, false>(exec);	\
	disp.regist<A, C, false>(exec);	\
	disp.regist<A, D, false>(exec);	\
	disp.regist<B, B, false>(exec);	\
	disp.regist<B, C, false>(exec);	\
	disp.regist<B, D, false>(exec);	\
	disp.regist<C, C, false>(exec);	\
	disp.regist<C, D, false>(exec);	\
	disp.regist<D, D, false>(exec);	\
	MyFunctorDispatcher symm;	\
	symm.regist<A, A, true>(exec);	\
	symm.regist<A, B, true>(exec);	\
	symm.regist<A, C, true>(exec);	\
	symm.regist<A, D, true>(exec);	\
	symm.regist<B, B, true>(exec);	\
	symm.regist<B, C, true>(exec);	\
	symm.regist<B, D, true>(exec);	\
	symm.regist<C, C, true>(exec);	\
	symm.regist<C, D, true>(exec);	\
	symm.regist<D, D, true>(exec);	\
	A a;	\
	B b;	\
	C c;	\
	D d;	\
	Base* p[4] = {&a, &b, &c, &d};	\
	for (size_t i = 0; i < 4; ++i)	\
	{	\
		for (size_t j = i; j < 4; ++j)	\
		{	\
			CPPUNIT_ASSERT_EQUAL((p[i]->id() << 4) | p[j]->id(), disp.dispatch(*p[i], *p[j]));	\
			CPPUNIT_ASSERT_EQUAL((p[i]->id() << 4) | p[j]->id(), symm.dispatch(*p[i], *p[j]));	\
		}	\
	}	\
	for (size_t i = 0; i < 4; ++i)	\
	{	\
		for (size_t j = 0; j < i; ++j)	\
		{	\
			CPPUNIT_ASSERT_EQUAL(static_cast<unsigned int>(0), disp.dispatch(*p[i], *p[j]));	\
			CPPUNIT_ASSERT_EQUAL((p[j]->id() << 4) | p[i]->id(), symm.dispatch(*p[i], *p[j]));	\
		}	\
	}

class MultimethodsTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(MultimethodsTest);
	CPPUNIT_TEST(testStaticDispatcher);
	CPPUNIT_TEST(testBasicFnDispatcher);
	CPPUNIT_TEST(testFastFnDispatcher);
	CPPUNIT_TEST(testBasicFunctorDispatcher);
	CPPUNIT_TEST(testFastFunctorDispatcher);
	CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp()
	{
	}

	virtual void tearDown()
	{
	}

private:
	void testStaticDispatcher()
	{
		using namespace multimethods_test;

		typedef StaticDispatcher<
			Base,
			boost::mpl::vector<A, B, C, D>,
			Base,
			boost::mpl::vector<A, B, C, D>,
			unsigned int
		> MyStaticDispatcher;

		A a;
		B b;
		C c;
		D d;
		Base* p[4] = {&a, &b, &c, &d};
		Executor exec;
		ExecutorSymmetric symm;

		for (size_t i = 0; i < 4; ++i)
		{
			for (size_t j = i; j < 4; ++j)
			{
				CPPUNIT_ASSERT_EQUAL((p[i]->id() << 4) | p[j]->id(), MyStaticDispatcher::dispatch(*p[i], *p[j], exec));
				CPPUNIT_ASSERT_EQUAL((p[i]->id() << 4) | p[j]->id(), MyStaticDispatcher::dispatch(*p[i], *p[j], symm));
			}
		}

		for (size_t i = 0; i < 4; ++i)
		{
			for (size_t j = 0; j < i; ++j)
			{
				CPPUNIT_ASSERT(((p[j]->id() << 4) | p[i]->id()) != MyStaticDispatcher::dispatch(*p[i], *p[j], exec));
				CPPUNIT_ASSERT_EQUAL((p[j]->id() << 4) | p[i]->id(), MyStaticDispatcher::dispatch(*p[i], *p[j], symm));
			}
		}
	}

	void testBasicFnDispatcher()
	{
		FN_DISPATCHER(BasicDispatcher)
	}

	void testFastFnDispatcher()
	{
		FN_DISPATCHER(FastDispatcher)
	}

	void testBasicFunctorDispatcher()
	{
		FUNCTOR_DISPATCHER(BasicDispatcher)
	}

	void testFastFunctorDispatcher()
	{
		FUNCTOR_DISPATCHER(FastDispatcher)	
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(MultimethodsTest);
