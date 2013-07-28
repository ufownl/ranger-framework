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

#include "ArMeshDataFileWriter.h"
#include "ArMeshTile.h"
#include "ArMeshData.h"
#include <string.h>
#include <stdexcept>

ArMeshDataFileWriter::ArMeshDataFileWriter(FILE* out)
	: mOut(out)
{
	if (!out)
	{
		throw std::invalid_argument("Invalid out.");
	}
}

bool ArMeshDataFileWriter::onVisit(ArMeshTile& obj)
{
	ArNavMeshTileHeader header;

	header.tileRef = obj.getRef();
	header.dataSize = obj.getSize();

	if (fwrite(&header, sizeof(header), 1, mOut) < 1)
	{
		return false;
	}

	if (fwrite(obj.getData(), obj.getSize(), 1, mOut) < 1)
	{
		return false;
	}

	return true;
}

bool ArMeshDataFileWriter::onVisit(ArMeshData& obj)
{
	ArNavMeshSetHeader header;

	header.magic = AR_NAVMESHSET_MAGIC;
	header.version = AR_NAVMESHSET_VERSION;
	header.numTiles = obj.getCount();
	memcpy(&header.params, &obj.getParams(), sizeof(dtNavMeshParams));

	if (fwrite(&header, sizeof(header), 1, mOut) < 1)
	{
		return false;
	}

	for (int i = 0; i < obj.getCount(); ++i)
	{
		ArMeshTile* tile = obj.getTile(i);

		if (tile && !serialize(*tile))
		{
			return false;
		}
	}

	return true;
}
