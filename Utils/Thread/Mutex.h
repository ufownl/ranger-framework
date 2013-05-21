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

#ifndef __Utils_Thread_Mutex_H__
#define __Utils_Thread_Mutex_H__

#include <boost/noncopyable.hpp>
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#else
#include <pthread.h>
#endif  // _WIN32 || _WIN64

class Mutex : private boost::noncopyable
{
public:
    Mutex();
    ~Mutex();

    void lock();
    void unlock();

private:
#if defined(_WIN32) || defined(_WIN64)
    CRITICAL_SECTION mCriticalSection;
#else
    pthread_mutex_t mMutex;
#endif  // _WIN32 || _WIN64
};

#endif  // __Utils_Thread_Mutex_H__
