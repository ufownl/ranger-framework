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

#ifndef __Utils_Thread_MutexCaller_H__
#define __Utils_Thread_MutexCaller_H__

#include "Thread/ScopedLock.h"
#include <assert.h>

template <class _ptr, class _lock = Mutex>
class MutexCaller
{
private:
    class Proxy
    {
    public:
        Proxy(MutexCaller *host)
            : mHost(host)
            , mLock(host->getLock())
        {
        }

        _ptr operator -> ()
        {
            return mHost->getInstance();
        }

    private:
        MutexCaller *mHost;
        ScopedLock<> mLock;
    };

public:
    MutexCaller(_ptr instance)
        : mInstance(instance)
    {
        assert(instance);
    }

    Proxy operator -> ()
    {
        return this;
    }

    _ptr getInstance()
    {
        return mInstance;
    }

    _lock& getLock()
    {
        return mLock;
    }

private:
    MutexCaller(const MutexCaller&);
    MutexCaller& operator = (MutexCaller&);

private:
    _ptr mInstance;
    _lock mLock;
};

#endif  // __Utils_Thread_MutexCaller_H__
