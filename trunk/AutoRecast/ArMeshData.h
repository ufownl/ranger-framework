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

#ifndef __AutoRecast_ArMeshData_H__
#define __AutoRecast_ArMeshData_H__

#include "ArMeshTile.h"
#include "Memory/STLAllocator.h"
#include <vector>

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define ArMeshData_Alloc	TCMallocAllocator
#else
#define ArMeshData_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class ArMeshData : public RefObject<ArMeshData_Alloc>
{
public:
	VISITABLE_DECL_NONVIRTUAL(ArMeshDataSerializer)

public:
	ArMeshData();
	ArMeshData(const dtNavMeshParams& params);

	void init(const dtNavMeshParams& params);

	const dtNavMeshParams& getParams() const;
	int getCount() const;

	bool addTile(ArMeshTilePtr tile);
	void removeTile(int idx);
	ArMeshTile* getTile(int idx) const;

private:
	typedef std::vector<
		ArMeshTilePtr,
		STLAllocator<ArMeshTilePtr, ArMeshData_Alloc>
	> tile_table_t;
	
	dtNavMeshParams mParams;
	tile_table_t mTiles;
	int mCount;
};

DeclareSmartPointer(ArMeshData);

#endif  // __AutoRecast_ArMeshData_H__
