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

#if !defined(_WIN32) && !defined(_WIN64)
	typedef std::stack<Coroutine*> CallStack;
#endif  // !_WIN32 && !_WIN64

public:
	Coroutine(const boost::function<void()>& func, size_t stackSize = 0);
	virtual ~Coroutine();

	template <class R>
	typename boost::add_reference<const R>::type resume()
	{
		resume_impl();
		return *static_cast<const R*>(mParams);
	}

	template <class R, class T>
	typename boost::add_reference<const R>::type resume(const T& ctx)
	{
		mParams = &ctx;
		return resume<R>();
	}

	template <class R>
	static typename boost::add_reference<const R>::type yield()
	{
		Instance* inst = getCurrentInstance();

		yield_impl(inst);
		return *static_cast<const R*>(inst->self->mParams);
	}

	template <class R, class T>
	static typename boost::add_reference<const R>::type yield(const T& ctx)
	{
		getCurrentInstance()->self->mParams = &ctx;
		return yield<R>();
	}

	State status();

private:
	struct Instance
	{
#if defined(_WIN32) || defined(_WIN64)
		void* fiber;
#endif  // _WIN32 || _WIN64
		State state;
		Coroutine* self;
#if defined(_WIN32) || defined(_WIN64)
		Instance* parent;
#else
        ucontext_t context;
        ucontext_t parent;
#endif  // _WIN32 || _WIN64
	};

private:
#if defined(_WIN32) || defined(_WIN64)
	static void __stdcall common_fiber_func(void* ctx);
#else
    static void common_context_func();
#endif  // _WIN32 || _WIN64
	static Instance* getCurrentInstance();
	static void yield_impl(Instance* inst);

	void resume_impl();

private:
	boost::function<void()> mFunc;
	Instance mInst;
	const void* mParams;
#if !defined(_WIN32) && !defined(_WIN64)
    char* mStack;

	static ThreadLocalStorage<CallStack> msCallStack;
#endif  // !_WIN32 && !_WIN64
};

template <> const void Coroutine::resume<void>();
template <> const void Coroutine::yield<void>();

DeclareSmartPointer(Coroutine);

#endif  // __Utils_Thread_Coroutine_H__
