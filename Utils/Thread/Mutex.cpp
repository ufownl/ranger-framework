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

#include "Thread/Mutex.h"

Mutex::Mutex()
{
#if defined(_WIN32) || defined(_WIN64)
    InitializeCriticalSection(&mCriticalSection);
#else
    pthread_mutex_init(&mMutex, 0);
#endif  // _WIN32 || _WIN64
}

Mutex::~Mutex()
{
#if defined(_WIN32) || defined(_WIN64)
    DeleteCriticalSection(&mCriticalSection);
#else
    pthread_mutex_destroy(&mMutex);
#endif  // _WIN32 || _WIN64
}

void Mutex::lock()
{
#if defined(_WIN32) || defined(_WIN64)
    EnterCriticalSection(&mCriticalSection);
#else
    pthread_mutex_lock(&mMutex);
#endif  // _WIN32 || _WIN64
}

void Mutex::unlock()
{
#if defined(_WIN32) || defined(_WIN64)
    LeaveCriticalSection(&mCriticalSection);
#else
    pthread_mutex_unlock(&mMutex);
#endif  // _WIN32 || _WIN64
}
