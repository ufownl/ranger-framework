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
#include "Object/Factory.h"

class FactoryTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(FactoryTest);
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
	struct Base
	{
		virtual ~Base()
		{
		}

		virtual unsigned short id() const = 0;
	};

	struct A : Base
	{
		virtual unsigned short id() const
		{
			return class_id();
		}

		static unsigned short class_id()
		{
			return 0;
		}

		static Base* create()
		{
			return new A;
		}
	};

	struct B : Base
	{
		virtual unsigned short id() const
		{
			return class_id();
		}

		static unsigned short class_id()
		{
			return 1;
		}

		static Base* create()
		{
			return new B;
		}
	};

	struct C : B 
	{
		virtual unsigned short id() const
		{
			return class_id();
		}

		static unsigned short class_id()
		{
			return 2;
		}

		static Base* create()
		{
			return new C;
		}
	};

	struct D : B
	{
		virtual unsigned short id() const
		{
			return class_id();
		}

		static unsigned short class_id()
		{
			return 3;
		}

		static Base* create()
		{
			return new D;
		}
	};

	template <class _id_type, template <class, class> class _storage_policy>
	void test_impl()
	{
		Factory<Base, _id_type, Base* (*)(), SingleThread, _storage_policy> f;
		
		f.regist(A::class_id(), &A::create);
		f.regist(B::class_id(), &B::create);
		f.regist(C::class_id(), &C::create);
		f.regist(D::class_id(), &D::create);

		for (unsigned short i = 0; i < 6; ++i)
		{
			Base* p = f.create(i);

			if (p)
			{
				CPPUNIT_ASSERT_EQUAL(i, p->id());
				delete p;
			}
			else
			{
				CPPUNIT_ASSERT(i >= 4);
			}
		}
	}

	void test()
	{
		test_impl<unsigned int, DefaultFactoryStorage>();
		test_impl<unsigned char, FastFactoryStorage>();
		test_impl<unsigned short, FastFactoryStorage>();
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(FactoryTest);
