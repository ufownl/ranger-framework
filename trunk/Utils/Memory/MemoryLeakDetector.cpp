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

#ifdef _DEBUG

#include "Memory/MemoryLeakDetector.h"
#include <stdio.h>

MemoryLeakDetector gMemoryLeakDetector;

MemoryLeakDetector::MemoryLeakDetector()
	: mStateProxy(&mState)
{
}

MemoryLeakDetector::~MemoryLeakDetector()
{
	if (!mStateProxy->empty())
	{
		fputs("Memory leak detected:\n", stderr);
		dumpMemoryState();
	}
}

void MemoryLeakDetector::onAllocate(void *p, size_t size, const char *file, long line)
{
	MemoryInfo info = {p, size, file, line};
	mStateProxy->push_back(info);
}

void MemoryLeakDetector::onDeallocate(void *p)
{
	MemoryInfo info = {p};
	mStateProxy->remove(info);
}

void MemoryLeakDetector::checkMemoryState(MemoryState &state)
{
	ScopedLock<> lock(mStateProxy.getLock());
	state = mState;
}

void MemoryLeakDetector::dumpDifferences(const MemoryState &s0, const MemoryState &s1)
{
	MemoryState state = s1;

	for (MemoryState::const_iterator i = s0.begin(); i != s0.end(); ++i)
	{
		state.remove(*i);
	}

	size_t total = 0;

	fputs("Dump differences:\n", stderr);
	for (MemoryState::iterator i = state.begin(); i != state.end(); ++i)
	{
		total += i->size;
        fprintf(stderr, "addr: 0x%08lX  size: %-4lu  file: %s (%ld)\n", (long unsigned int)i->addr, i->size, i->file, i->line);
	}
	fprintf(stderr, "Total: %lu bytes.\n", total);
}

void MemoryLeakDetector::dumpMemoryState()
{
	ScopedLock<> lock(mStateProxy.getLock());
	size_t total = 0;

	for (MemoryState::iterator i = mState.begin(); i != mState.end(); ++i)
	{
		total += i->size;
        fprintf(stderr, "addr: 0x%08lX  size: %-4lu  file: %s (%ld)\n", (long unsigned int)i->addr, i->size, i->file, i->line);
	}
	fprintf(stderr, "Total: %lu bytes.\n", total);
}

#endif  // _DEBUG
