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

#ifndef __RangerFramework_RfService_H__
#define __RangerFramework_RfService_H__

#include "Object/RefObject.h"
#include "Object/SmartPointer.h"

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define RfService_Alloc	TCMallocAllocator
#else
#define RfService_Alloc Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class RfServiceManager;

class RfService : public RefObject<RfService_Alloc, unsigned int, SingleThread>
{
	friend class RfServiceManager;

public:
	RfService();
	virtual ~RfService();

	bool tick();
	void shutdown();

protected:
	virtual bool onInitialize();
	virtual bool onTick(long escape);
	virtual void onShutdown();

	long getInitTime() const;
	long getTickTime() const;
	RfServiceManager* getManager() const;

private:
	long mInitTime;
	long mTickTime;
	bool mIsInitialized;
	RfServiceManager* mManager;
};

DeclareSmartPointer(RfService);

#endif  // __RangerFramework_RfService_H__
