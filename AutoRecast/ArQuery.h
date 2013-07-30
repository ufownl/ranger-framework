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

#ifndef __AutoRecast_ArQuery_H__
#define __AutoRecast_ArQuery_H__

#include "Object/RefObject.h"
#include "Object/SmartPointer.h"
#include <DetourNavMeshQuery.h>

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define ArQuery_Alloc	TCMallocAllocator
#else
#define ArQuery_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class ArMesh;

class ArQuery : public RefObject<ArQuery_Alloc>
{
public:
	ArQuery();
	virtual ~ArQuery();

	dtStatus init(const ArMesh* mesh, int maxNodes);

	dtStatus initSlicedFindPath(dtPolyRef startRef, dtPolyRef endRef
			, const float* startPos, const float* endPos, const dtQueryFilter* filter);
	dtStatus updateSlicedFindPath(int maxIter, int* doneIters);
	dtStatus finalizeSlicedFindPath(dtPolyRef* path, int* pathCount, int maxPath);
	dtStatus finalizeSlicedFindPathPartial(
			const dtPolyRef* existing, int existingSize, dtPolyRef* path, int* pathCount, int maxPath);

	const dtNavMeshQuery* backend() const;

private:
	dtNavMeshQuery* mBackend;
};

DeclareSmartPointer(ArQuery);

#endif  // __AutoRecast_ArQuery_H__
