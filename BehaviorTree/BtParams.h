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

#ifndef __BehaviorTree_BtParams_H__
#define __BehaviorTree_BtParams_H__

#include "Object/RefObject.h"
#include "Object/SmartPointer.h"
#include "Memory/std_tcmalloc_allocator.h"
#include <vector>

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define BtParams_Alloc	TCMallocAllocator
#else
#define BtParams_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class BtParams : public RefObject<BtParams_Alloc, unsigned int, SingleThread>
{
public:
	union BtCacheValue
	{
		bool bool_v;
		char char_v;
		unsigned char uchar_v;
		short short_v;
		unsigned short ushort_v;
		int int_v;
		unsigned int uint_v;
		long long_v;
		unsigned long ulong_v;
		long long longlong_v;
		unsigned long long ulonglong_v;
		float float_v;
		double double_v;
	};

public:
	BtParams(size_t size);

	void setCacheData(size_t idx, const BtCacheValue& val);
	const BtCacheValue* getCacheData(size_t idx) const;
	void resetCacheData();

	void setExtraData(void* extra);
	void* getExtraData();

private:
	struct BtCache
	{
		BtCacheValue value;
		bool cache;

		BtCache()
			: cache(false)
		{
		}
	};

private:
	typedef std::vector<BtCache, std_alloc<BtCache> > BtCacheTable;

	BtCacheTable mCache;
	void* mExtra;
};

DeclareSmartPointer(BtParams);

#endif  // __BehaviorTree_BtParams_H__
