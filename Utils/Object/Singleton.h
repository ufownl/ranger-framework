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

#ifndef __Utils_Object_Singleton_H__
#define __Utils_Object_Singleton_H__

#include "Thread/ThreadPolicy.h"
#include "Thread/ScopedLock.h"
#if !defined(_WIN32) && !defined(_WIN64)
#include "Thread/ThreadLocalStorage.h"
#endif  // !_WIN32 && !_WIN64
#include <stdexcept>

template <class T, class _thread_policy>
class DefaultSingletonStorage
{
public:
	typedef typename _thread_policy::template Data<T*>::type StorageType;

protected:
	static StorageType msInstance;
};

template <class T, class _thread_policy>
typename _thread_policy::template Data<T*>::type DefaultSingletonStorage<T, _thread_policy>::msInstance = static_cast<T*>(0);

template <class T, class _thread_policy>
class TlsSingletonStorage
{
#if defined(_WIN32) || defined(_WIN64)

public:
	typedef T* StorageType;

protected:
	__declspec(thread) static StorageType msInstance;

#else

public:
	typedef ThreadLocalStorage<T> StorageType;

protected:
	static StorageType msInstance;

#endif  // _WIN32 || _WIN64
};

template <class T, class _thread_policy>
#if defined(_WIN32) || defined(_WIN64)
T* TlsSingletonStorage<T, _thread_policy>::msInstance = static_cast<T*>(0);
#else
ThreadLocalStorage<T> TlsSingletonStorage<T, _thread_policy>::msInstance = static_cast<T*>(0);
#endif  // _WIN32 || _WIN64

template <
	class T,
	template <class> class _thread_policy = ClassLevelLockable,
	template <class, class> class _storage_policy = DefaultSingletonStorage
>
class Singleton
	: public _thread_policy<Singleton<T, _thread_policy, _storage_policy> >
	, public _storage_policy<T, _thread_policy<Singleton<T, _thread_policy, _storage_policy> > >
{
public:
	typedef _thread_policy<Singleton<T, _thread_policy, _storage_policy> > ThreadPolicy;
	typedef _storage_policy<T, ThreadPolicy> StoragePolicy;

public:
    Singleton()
		: mExcept(false)
	{
		typename ThreadPolicy::Lock l;
		ScopedLock<typename ThreadPolicy::Lock> sl(l);

		if (StoragePolicy::msInstance)
		{
			mExcept = true;
			throw std::runtime_error("Singleton has been created.");
		}

		StoragePolicy::msInstance = static_cast<T*>(this);
	}
	
    ~Singleton()
	{
		if (!mExcept)
		{
			typename ThreadPolicy::Lock l;
			ScopedLock<typename ThreadPolicy::Lock> sl(l);
			StoragePolicy::msInstance = 0;
		}
	}

    static T& getSingleton()
	{
		return *StoragePolicy::msInstance;
	}

    static T* getSingletonPtr()
	{
		return StoragePolicy::msInstance;
	}

private:
    Singleton(const Singleton<T>&);
    Singleton& operator = (const Singleton<T>&);

private:
	bool mExcept;
};

template <class T>
struct SingletonStaticCreation
{
	static T* create()
	{
		static T obj;
		return &obj;
	}

	static void destroy(T*)
	{
	}
};

template <class T>
struct SingletonOpNewCreation
{
	static T* create()
	{
		return new T;
	}

	static void destroy(T* p)
	{
		delete p;
	}
};

#ifndef RfNew
#ifdef _DEBUG
#define RfNew	new(__FILE__, __LINE__)
#else
#define RfNew	new
#endif  // _DEBUG
#endif  // RfNew

template <class T>
struct SingletonOpRfNewCreation
{
	static T* create()
	{
		return RfNew T;
	}

	static void destroy(T* p)
	{
		delete p;
	}
};

template <
	class T,
	template <class> class _creation_policy = SingletonStaticCreation,
	template <class> class _thread_policy = ClassLevelLockable,
	template <class, class> class _storage_policy = DefaultSingletonStorage
>
class SingletonHolder
	: public _thread_policy<SingletonHolder<T, _creation_policy, _thread_policy, _storage_policy> >
	, public _storage_policy<T, _thread_policy<SingletonHolder<T, _creation_policy, _thread_policy, _storage_policy> > >
{
public:
	typedef _creation_policy<T> CreationPolicy;
	typedef _thread_policy<SingletonHolder<T, _creation_policy, _thread_policy, _storage_policy> > ThreadPolicy;
	typedef _storage_policy<T, ThreadPolicy> StoragePolicy;

public:
	static T& instance()
	{
		if (!StoragePolicy::msInstance)
		{
			typename ThreadPolicy::Lock l;
			ScopedLock<typename ThreadPolicy::Lock> sl(l);

			if (!StoragePolicy::msInstance)
			{
				StoragePolicy::msInstance = CreationPolicy::create();
			}
		}

		return *StoragePolicy::msInstance;
	}

	static void destroy()
	{
		CreationPolicy::destroy(StoragePolicy::msInstance);
		StoragePolicy::msInstance = 0;
	}
};

#endif  // __Utils_Object_Singleton_H__
