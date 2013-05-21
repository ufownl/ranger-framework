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

#ifndef __Utils_Memory_MemoryLeakDetector_H__
#define __Utils_Memory_MemoryLeakDetector_H__

#include "Object/Singleton.h"
#include "Thread/MutexCaller.h"
#include <list>

struct MemoryInfo
{
    void *addr;
    size_t size;
    const char *file;
    long line;

    bool operator == (const MemoryInfo &rhs)
    {
        return addr == rhs.addr;
    }
};

typedef std::list<MemoryInfo> MemoryState;

class MemoryLeakDetector
	: public Singleton<MemoryLeakDetector>
	, private boost::noncopyable
{
public:
    MemoryLeakDetector();
    ~MemoryLeakDetector();

    void onAllocate(void *p, size_t size, const char *file, long line);
    void onDeallocate(void *p);

    void checkMemoryState(MemoryState &state);
    void dumpMemoryState();

    static void dumpDifferences(const MemoryState &s0, const MemoryState &s1);

private:
    MemoryState mState;
    MutexCaller<MemoryState*> mStateProxy;
};

#endif  // __Utils_Memory_MemoryLeakDetector_H__
