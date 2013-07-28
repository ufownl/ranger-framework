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

#ifndef __AutoRecast_ArMeshDataSerializer_H__
#define __AutoRecast_ArMeshDataSerializer_H__

#include "Object/RefObject.h"
#include "Object/SmartPointer.h"
#include "Object/Visitor.h"
#include <DetourNavMesh.h>
#include <boost/mpl/vector.hpp>

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define ArMeshDataSerializer_Alloc	TCMallocAllocator
#else
#define ArMeshDataSerializer_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class ArMeshTile;
class ArMeshData;

class ArMeshDataSerializer
	: public Visitor<boost::mpl::vector<ArMeshTile, ArMeshData>, bool>
	, public RefObject<ArMeshDataSerializer_Alloc>
{
public:
	template <class T>
	bool serialize(T& obj)
	{
		return obj.accept(*this);
	}
};

DeclareSmartPointer(ArMeshDataSerializer);

#define AR_NAVMESHSET_MAGIC		('M' << 24 | 'S' << 16 | 'E' << 8 | 'T')
#define AR_NAVMESHSET_VERSION	1

struct ArNavMeshSetHeader
{
	int magic;
	int version;
	int numTiles;
	dtNavMeshParams params;
};

struct ArNavMeshTileHeader
{
	dtTileRef tileRef;
	int dataSize;
};

#endif  // __AutoRecast_ArMeshDataSerializer_H__
