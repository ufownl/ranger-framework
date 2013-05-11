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

#ifndef __Utils_Thread_ThreadLocalStorage_H__
#define __Utils_Thread_ThreadLocalStorage_H__

#include <pthread.h>

template <class T>
class ThreadLocalStorage
{
public:
	typedef void (*free_func_t)(void*);

public:
	ThreadLocalStorage(free_func_t free_func = 0)
	{
		pthread_key_create(&mKey, free_func);
	}

	ThreadLocalStorage(T* p, free_func_t free_func = 0)
	{
		pthread_key_create(&mKey, free_func);
		pthread_setspecific(mKey, p);
	}

	~ThreadLocalStorage()
	{
		pthread_key_delete(mKey);
	}

	ThreadLocalStorage& operator = (T* p)
	{
		pthread_setspecific(mKey, p);
		return *this;
	}

	operator bool ()
	{
		return pthread_getspecific(mKey) != 0;
	}

	bool operator ! ()
	{
		return pthread_getspecific(mKey) == 0;
	}

	operator T* ()
	{
		return static_cast<T*>(pthread_getspecific(mKey));
	}
	
	T& operator * ()
	{
		return *static_cast<T*>(pthread_getspecific(mKey));
	}

	T* operator -> ()
	{
		return static_cast<T*>(pthread_getspecific(mKey));
	}

private:
	pthread_key_t mKey;
};

#endif  // __Utils_Thread_ThreadLocalStorage_H__
