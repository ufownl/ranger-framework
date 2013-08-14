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

#include "Thread/Coroutine.h"

#if !defined(_WIN32) && !defined(_WIN64)

void release_callstack(void* p)
{
	if (!p) return;
	static_cast<Coroutine::CallStack*>(p)->~stack();
	Coroutine_Alloc::deallocate(p);
}

Coroutine::TLSCS::TLSCS()
	: ThreadLocalStorage(release_callstack)
{
}

Coroutine::TLSCS::~TLSCS()
{
	release_callstack(*this);
}

Coroutine::TLSCS& Coroutine::TLSCS::operator = (CallStack* p)
{
	*static_cast<ThreadLocalStorage<CallStack>*>(this) = p;
	return *this;
}

#endif  // !_WIN32 && !_WIN64

Coroutine::Coroutine(const boost::function<void()>& func, size_t stackSize /* = 0 */)
	: mFunc(func)
	, mParams(0)
#if !defined(_WIN32) && !defined(_WIN64)
	, mStack(0)
#endif  // !_WIN32 && !_WIN64
{
#if defined(_WIN32) || defined(_WIN64)
	__declspec(thread) static Instance root = {0, eRUNNING, 0, 0};

	if (root.fiber == 0)
	{
		root.fiber = ConvertThreadToFiber(&root);
		assert(root.fiber);
	}

	mInst.fiber = CreateFiber(stackSize, &common_fiber_func, &mInst);
	assert(mInst.fiber);
#endif  // _WIN32 || _WIN64
	mInst.state = eSUSPENDED;
	mInst.self = this;
#if defined(_WIN32) || defined(_WIN64)
	mInst.parent = 0;
#else

    if (stackSize == 0)
    {
        stackSize = 1024 * 1024;
    }

#ifdef _DEBUG
    mStack = static_cast<char*>(Coroutine_Alloc::allocate(stackSize, __FILE__, __LINE__));
#else
    mStack = static_cast<char*>(Coroutine_Alloc::allocate(stackSize));
#endif  // _DEBUG
    if (!mStack) throw std::bad_alloc();

    getcontext(&mInst.context);
    mInst.context.uc_link = &mInst.parent;
    mInst.context.uc_stack.ss_sp = mStack;
    mInst.context.uc_stack.ss_size = stackSize;
    makecontext(&mInst.context, &Coroutine::common_context_func, 0);
#endif  // _WIN32 || _WIN64
}

Coroutine::~Coroutine()
{
#if defined(_WIN32) || defined(_WIN64)
	if (mInst.fiber)
	{
		DeleteFiber(mInst.fiber);
	}
#else
	if (mStack)
	{
		Coroutine_Alloc::deallocate(mStack);
	}
#endif  // _WIN32 || _WIN64
}

template <>
const void Coroutine::resume<void>()
{
    resume_impl();
}

template <>
const void Coroutine::yield<void>()
{
    yield_impl(getCurrentInstance());
}

Coroutine::State Coroutine::status()
{
	return mInst.state;
}

#if defined(_WIN32) || defined(_WIN64)
void Coroutine::common_fiber_func(void* ctx)
{
	Instance* inst = static_cast<Instance*>(ctx);

	inst->self->mFunc();
	inst->state = eDEAD;

	if (inst->parent->fiber)
	{
		SwitchToFiber(inst->parent->fiber);
	}
}
#else
void Coroutine::common_context_func()
{
    Instance* inst = getCurrentInstance();

    inst->self->mFunc();
    inst->state = eDEAD;
	assert(TlscsHolder::instance());
    TlscsHolder::instance()->pop();
}
#endif  // _WIN32 || _WIN64

Coroutine::Instance* Coroutine::getCurrentInstance()
{
#if defined(_WIN32) || defined(_WIN64)
	return static_cast<Instance*>(GetFiberData());
#else
	assert(TlscsHolder::instance());
    return &TlscsHolder::instance()->top()->mInst;
#endif  // _WIN32 || _WIN64
}

void Coroutine::yield_impl(Instance* inst)
{
#if defined(_WIN32) || defined(_WIN64)
	if (inst->parent && inst->parent->fiber)
	{
		inst->state = eSUSPENDED;
		SwitchToFiber(inst->parent->fiber);
	}
#else
	assert(TlscsHolder::instance());
    if (!TlscsHolder::instance()->empty())
    {
        inst->state = eSUSPENDED;
        TlscsHolder::instance()->pop();
        swapcontext(&inst->context, &inst->parent);
    }
#endif  // _WIN32 || _WIN64
}

void Coroutine::resume_impl()
{
#if defined(_WIN32) || defined(_WIN64)
	if (mInst.state == eSUSPENDED && mInst.fiber)
	{
		mInst.state = eRUNNING;
		mInst.parent = getCurrentInstance();
		SwitchToFiber(mInst.fiber);
	}
#else
    if (mInst.state == eSUSPENDED)
    {
        mInst.state = eRUNNING;
		if (!TlscsHolder::instance())
		{
#ifdef _DEBUG
			void* p = Coroutine_Alloc::allocate(sizeof(CallStack), __FILE__, __LINE__);
#else
			void* p = Coroutine_Alloc::allocate(sizeof(CallStack));
#endif  // _DEBUG
			if (!p) throw std::bad_alloc();
			TlscsHolder::instance() = new(p) CallStack;
		}
        TlscsHolder::instance()->push(this);
        swapcontext(&mInst.parent, &mInst.context);
    }
#endif  // _WIN32 || _WIN64
}
