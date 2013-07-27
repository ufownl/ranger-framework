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

#ifndef __AutoRecast_ArMeshTile_H__
#define __AutoRecast_ArMeshTile_H__

#include "Object/RefObject.h"
#include "Object/SmartPointer.h"
#include <DetourNavMesh.h>

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define ArMeshTile_Alloc	TCMallocAllocator
#else
#define ArMeshTile_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class ArMeshTile : public RefObject<ArMeshTile_Alloc>
{
public:
	ArMeshTile(unsigned char* data, int size, dtTileRef ref = 0);
	virtual ~ArMeshTile();

	unsigned char* getData() const;
	int getSize() const;
	dtTileRef getRef() const;

private:
	unsigned char* mData;
	int mSize;
	dtTileRef mRef;
};

DeclareSmartPointer(ArMeshTile);

#endif  // __AutoRecast_ArMeshTile_H__
