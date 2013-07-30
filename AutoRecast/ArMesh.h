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

#ifndef __AutoRecast_ArMesh_H__
#define __AutoRecast_ArMesh_H__

#include "Object/RefObject.h"
#include "Object/SmartPointer.h"
#include <DetourNavMesh.h>

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define ArMesh_Alloc	TCMallocAllocator
#else
#define ArMesh_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class ArMeshTile;

class ArMesh : public RefObject<ArMesh_Alloc>
{
public:
	ArMesh();
	virtual ~ArMesh();

	dtStatus init(const dtNavMeshParams& params);
	dtStatus addTile(const ArMeshTile* tile, dtTileRef* ref = 0);
	dtStatus removeTile(dtTileRef ref);

	dtStatus setPolyFlags(dtPolyRef ref, unsigned short flags);
	dtStatus setPolyArea(dtPolyRef ref, unsigned char area);
	dtStatus restoreTileState(dtMeshTile* tile, const unsigned char* data, int maxDataSize);

	const dtNavMesh* backend() const;

private:
	dtNavMesh* mBackend;
};

DeclareSmartPointer(ArMesh);

#endif  // __AutoRecast_ArMesh_H__
