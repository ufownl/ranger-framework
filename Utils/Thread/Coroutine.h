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

#ifndef __Utils_Thread_Coroutine_H__
#define __Utils_Thread_Coroutine_H__

#include "Object/RefObject.h"
#include "Object/SmartPointer.h"
#if !defined(_WIN32) && !defined(_WIN64)
#include "Thread/ThreadLocalStorage.h"
#endif  // !_WIN32 && !_WIN64
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/identity.hpp>
#if !defined(_WIN32) && !defined(_WIN64)
#include <stack>
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE
#endif  // _XOPEN_SOURCE
#include <ucontext.h>
#endif  // !_WIN32 && !_WIN64

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define Coroutine_Alloc	TCMallocAllocator
#else
#define Coroutine_Alloc Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class Coroutine : public RefObject<Coroutine_Alloc, unsigned int, SingleThread>
{
public:
	enum State {
		eSUSPENDED, eRUNNING, eDEAD
	};

	template <class T>
	struct param_type
		: boost::mpl::eval_if<
			boost::mpl::or_<
				boost::is_scalar<T>,
				boost::is_void<T>,
				boost::is_stateless<T>,
				boost::is_reference<T>
			>,
			boost::mpl::identity<T>,
			boost::add_reference<const T>
		>
	{
	};

	typedef std::stack<Coroutine*> CallStack;

	typedef void* (*alloc_func)(size_t);
	typedef void (*dealloc_func)(void*);

public:
	Coroutine(const boost::function<void()> &func, size_t stackSize = 0, alloc_func alloc = malloc, dealloc_func dealloc = free);
	virtual ~Coroutine();

	template <class R>
	typename param_type<R>::type resume()
	{
		resume_impl();
		return *static_cast<typename boost::add_pointer<typename boost::remove_reference<R>::type>::type>(mParams);
	}

	template <class R, class T>
	typename param_type<R>::type resume(typename param_type<T>::type ctx)
	{
		mParams = static_cast<void*>(
			const_cast<typename boost::add_pointer<typename boost::remove_reference<T>::type>::type>(&ctx));
		return resume<R>();
	}

	template <class R>
	static typename param_type<R>::type yield() {
		Instance *inst = getCurrentInstance();

		yield_impl(inst);
		return *static_cast<typename boost::add_pointer<typename boost::remove_reference<R>::type>::type>(inst->self->mParams);
	}

	template <class R, class T>
	static typename param_type<R>::type yield(typename param_type<T>::type ctx)
	{
		getCurrentInstance()->self->mParams = static_cast<void*>(
			const_cast<typename boost::add_pointer<typename boost::remove_reference<T>::type>::type>(&ctx));
		return yield<R>();
	}

	State status();

private:
	struct Instance
	{
#if defined(_WIN32) || defined(_WIN64)
		void *fiber;
#endif  // _WIN32 || _WIN64
		State state;
		Coroutine *self;
#if defined(_WIN32) || defined(_WIN64)
		Instance *parent;
#else
        ucontext_t context;
        ucontext_t parent;
#endif  // _WIN32 || _WIN64
	};

private:
#if defined(_WIN32) || defined(_WIN64)
	static void __stdcall common_fiber_func(void *ctx);
#else
    static void common_context_func();
#endif  // _WIN32 || _WIN64
	static Instance* getCurrentInstance();
	static void yield_impl(Instance *inst);

	void resume_impl();

private:
	boost::function<void()> mFunc;
	Instance mInst;
	void *mParams;
#if !defined(_WIN32) && !defined(_WIN64)
    dealloc_func mDealloc;
    char *mStack;

	static ThreadLocalStorage<CallStack> msCallStack;
#endif  // !_WIN32 && !_WIN64
};

template <> void Coroutine::resume<void>();
template <> void Coroutine::yield<void>();

DeclareSmartPointer(Coroutine);

#endif  // __Utils_Thread_Coroutine_H__
