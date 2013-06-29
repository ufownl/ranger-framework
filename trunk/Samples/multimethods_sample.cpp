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

#include "Multimethods/StaticDispatcher.h"
#include "Multimethods/DynamicDispatcher.h"
#include <boost/mpl/vector.hpp>
#include <vector>
#include <stdio.h>

struct Base
{
	virtual ~Base() {}
};

struct A : Base
{
};

struct B : Base
{
};

struct C : B
{
};

struct D : B
{
};

struct Executor
{
	void operator () (A&, A&)
	{
		puts("A A");
	}
	
	void operator () (A&, B&)
	{
		puts("A B");
	}
	
	void operator () (A&, C&)
	{
		puts("A C");
	}
	
	void operator () (A&, D&)
	{
		puts("A D");
	}
	
	void operator () (B&, B&)
	{
		puts("B B");
	}
	
	void operator () (B&, C&)
	{
		puts("B C");
	}
	
	void operator () (B&, D&)
	{
		puts("B D");
	}
	
	void operator () (C&, C&)
	{
		puts("C C");
	}
	
	void operator () (C&, D&)
	{
		puts("C D");
	}
	
	void operator () (D&, D&)
	{
		puts("D D");
	}
	
	void operator () (Base&, Base&)
	{
		puts("Base Base");
	}
};

struct Executor_Symmetric : Executor
{
};

template <>
struct is_symmetric<Executor_Symmetric> : boost::mpl::true_
{
};

void static_dispatcher_sample()
{
	putchar('\n');
	puts(__FUNCTION__);
	putchar('\n');

	typedef StaticDispatcher<Base, boost::mpl::vector<A, B, C, D> > MyStaticDispatcher;

	Executor exec;
	Executor_Symmetric symm;
	std::vector<Base*> v(4);

	v[0] = new A;
	v[1] = new B;
	v[2] = new C;
	v[3] = new D;

	for (std::vector<Base*>::iterator i = v.begin(); i != v.end(); ++i)
	{
		for (std::vector<Base*>::iterator j = v.begin(); j != v.end(); ++j)
		{
			Base& l = **i;
			Base& r = **j;

			printf("dispatch %s %s\n", typeid(l).name(), typeid(r).name());
			printf("exec ");
			MyStaticDispatcher::dispatch(l, r, exec);
			printf("symm ");
			MyStaticDispatcher::dispatch(l, r, symm);
		}
	}

	for (std::vector<Base*>::iterator i = v.begin(); i != v.end(); ++i)
	{
		delete *i;
	}
}

void ExecAA(A&, A&)
{
	puts("A A");
}

void ExecAB(A&, B&)
{
	puts("A B");
}

void ExecAC(A&, C&)
{
	puts("A C");
}

void ExecAD(A&, D&)
{
	puts("A D");
}

void ExecBB(B&, B&)
{
	puts("B B");
}

void ExecBC(B&, C&)
{
	puts("B C");
}

void ExecBD(B&, D&)
{
	puts("B D");
}

void ExecCC(C&, C&)
{
	puts("C C");
}

void ExecCD(C&, D&)
{
	puts("C D");
}

void ExecDD(D&, D&)
{
	puts("D D");
}

void basic_fn_dispatcher_sample()
{
	putchar('\n');
	puts(__FUNCTION__);
	putchar('\n');

	FnDispatcher<Base> disp;

	disp.regist<A, A, ExecAA, false>();
	disp.regist<A, B, ExecAB, false>();
	disp.regist<A, C, ExecAC, false>();
	disp.regist<A, D, ExecAD, false>();
	disp.regist<B, B, ExecBB, false>();
	disp.regist<B, C, ExecBC, false>();
	disp.regist<B, D, ExecBD, false>();
	disp.regist<C, C, ExecCC, false>();
	disp.regist<C, D, ExecCD, false>();
	disp.regist<D, D, ExecDD, false>();

	FnDispatcher<Base> symm;

	symm.regist<A, A, ExecAA, true>();
	symm.regist<A, B, ExecAB, true>();
	symm.regist<A, C, ExecAC, true>();
	symm.regist<A, D, ExecAD, true>();
	symm.regist<B, B, ExecBB, true>();
	symm.regist<B, C, ExecBC, true>();
	symm.regist<B, D, ExecBD, true>();
	symm.regist<C, C, ExecCC, true>();
	symm.regist<C, D, ExecCD, true>();
	symm.regist<D, D, ExecDD, true>();

	std::vector<Base*> v(4);

	v[0] = new A;
	v[1] = new B;
	v[2] = new C;
	v[3] = new D;

	for (std::vector<Base*>::iterator i = v.begin(); i != v.end(); ++i)
	{
		for (std::vector<Base*>::iterator j = v.begin(); j != v.end(); ++j)
		{
			Base& l = **i;
			Base& r = **j;

			printf("dispatch %s %s\n", typeid(l).name(), typeid(r).name());
			printf("exec ");
			try
			{
				disp.dispatch(l, r);
			}
			catch (std::invalid_argument& e)
			{
				puts(e.what());
			}
			printf("symm ");
			try
			{
				symm.dispatch(l, r);
			}
			catch (std::invalid_argument& e)
			{
				puts(e.what());
			}
		}
	}

	for (std::vector<Base*>::iterator i = v.begin(); i != v.end(); ++i)
	{
		delete *i;
	}
}

void basic_functor_dispatcher_sample()
{
	putchar('\n');
	puts(__FUNCTION__);
	putchar('\n');

	Executor exec;

	FunctorDispatcher<Base> disp;

	disp.regist<A, A, false>(exec);
	disp.regist<A, B, false>(exec);
	disp.regist<A, C, false>(exec);
	disp.regist<A, D, false>(exec);
	disp.regist<B, B, false>(exec);
	disp.regist<B, C, false>(exec);
	disp.regist<B, D, false>(exec);
	disp.regist<C, C, false>(exec);
	disp.regist<C, D, false>(exec);
	disp.regist<D, D, false>(exec);

	FunctorDispatcher<Base> symm;

	symm.regist<A, A, true>(exec);
	symm.regist<A, B, true>(exec);
	symm.regist<A, C, true>(exec);
	symm.regist<A, D, true>(exec);
	symm.regist<B, B, true>(exec);
	symm.regist<B, C, true>(exec);
	symm.regist<B, D, true>(exec);
	symm.regist<C, C, true>(exec);
	symm.regist<C, D, true>(exec);
	symm.regist<D, D, true>(exec);

	std::vector<Base*> v(4);

	v[0] = new A;
	v[1] = new B;
	v[2] = new C;
	v[3] = new D;

	for (std::vector<Base*>::iterator i = v.begin(); i != v.end(); ++i)
	{
		for (std::vector<Base*>::iterator j = v.begin(); j != v.end(); ++j)
		{
			Base& l = **i;
			Base& r = **j;

			printf("dispatch %s %s\n", typeid(l).name(), typeid(r).name());
			printf("exec ");
			try
			{
				disp.dispatch(l, r);
			}
			catch (std::invalid_argument& e)
			{
				puts(e.what());
			}
			printf("symm ");
			try
			{
				symm.dispatch(l, r);
			}
			catch (std::invalid_argument& e)
			{
				puts(e.what());
			}
		}
	}

	for (std::vector<Base*>::iterator i = v.begin(); i != v.end(); ++i)
	{
		delete *i;
	}
}

int main()
{
	static_dispatcher_sample();
	basic_fn_dispatcher_sample();
	basic_functor_dispatcher_sample();
	return 0;
}
