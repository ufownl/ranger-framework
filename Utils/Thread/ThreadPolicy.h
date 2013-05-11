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

#ifndef __Utils_Thread_ThreadPolicy_H__
#define __Utils_Thread_ThreadPolicy_H__

#include "Thread/Mutex.h"

template <class T>
struct ClassLevelLockable
{
	class Lock
	{
	public:
		Lock()
		{
			initialize();
		}

		Lock(T&)
		{
			initialize();
		}

		void lock()
		{
			mMutex->lock();
		}

		void unlock()
		{
			mMutex->unlock();
		}

	private:
		void initialize()
		{
			static Mutex mutex;
			mMutex = &mutex;
		}

	private:
		Mutex* mMutex;
	};

	template <class _type>
	struct Data
	{
		typedef volatile _type type;
	};
};

template <class T>
class ObjectLevelLockable
{
public:
	class Lock
	{
	public:
		Lock(T& obj)
			: mObj(obj)
		{
		}

		void lock()
		{
			mObj.mMutex.lock();
		}

		void unlock()
		{
			mObj.mMutex.unlock();
		}

	private:
		T& mObj;
	};

	template <class _type>
	struct Data
	{
		typedef volatile _type type;
	};

protected:
	Mutex mMutex;
};

template <class T>
struct SingleThread
{
	struct Lock
	{
		Lock()
		{
		}

		Lock(T&)
		{
		}

		void lock()
		{
		}

		void unlock()
		{
		}
	};

	template <class _type>
	struct Data
	{
		typedef _type type;
	};
};

#endif  // __Utils_Thread_ThreadPolicy_H__
