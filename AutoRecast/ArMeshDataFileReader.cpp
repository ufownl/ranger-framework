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

#include "ArMeshDataFileReader.h"
#include "ArMeshTile.h"
#include "ArMeshData.h"
#include <string.h>
#include <stdexcept>

ArMeshDataFileReader::ArMeshDataFileReader(FILE* in)
	: mIn(in)
{
	if (!in)
	{
		throw std::invalid_argument("Invalid in.");
	}
}

bool ArMeshDataFileReader::onVisit(ArMeshTile& obj)
{
	ArNavMeshTileHeader header;

	if (fread(&header, sizeof(header), 1, mIn) < 1)
	{
		return false;
	}

	if (!header.dataSize)
	{
		return false;
	}

	unsigned char* data = static_cast<unsigned char*>(dtAlloc(header.dataSize, DT_ALLOC_PERM));

	if (!data)
	{
		return false;
	}

	if (fread(data, header.dataSize, 1, mIn) < 1)
	{
		dtFree(data);
		return false;
	}

	obj.initialize(data, header.dataSize, header.tileRef);

	return true;
}

bool ArMeshDataFileReader::onVisit(ArMeshData& obj)
{
	ArNavMeshSetHeader header;

	if (fread(&header, sizeof(header), 1, mIn) < 1)
	{
		return false;
	}

	if (header.magic != AR_NAVMESHSET_MAGIC)
	{
		return false;
	}

	if (header.version != AR_NAVMESHSET_VERSION)
	{
		return false;
	}

	try
	{
		obj.initialize(header.params);

		for (int i = 0; i < header.numTiles; ++i)
		{
			ArMeshTilePtr tile = RfNew ArMeshTile;

			if (!serialize(*tile))
			{
				return false;
			}

			if (!obj.addTile(tile))
			{
				return false;
			}
		}

		return true;
	}
	catch (const std::bad_alloc& e)
	{
		return false;
	}
}
