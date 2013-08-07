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

#include "ArMeshExporter.h"
#include "ArMeshTile.h"
#include "ArMeshData.h"
#include "ArMesh.h"
#include <string.h>

ArMeshExporter::ArMeshExporter(const ArMesh& mesh)
	: mMesh(mesh)
{
}

bool ArMeshExporter::onVisit(ArMeshTile& obj)
{
	return true;
}

bool ArMeshExporter::onVisit(ArMeshData& obj)
{
	if (!mMesh.backend())
	{
		return false;
	}

	obj.init(*mMesh.backend()->getParams());

	for (int i = 0; i < mMesh.backend()->getMaxTiles(); ++i)
	{
		const dtMeshTile* t = mMesh.backend()->getTile(i);

		if (!t || !t->header || !t->dataSize)
		{
			continue;
		}

		unsigned char* data = static_cast<unsigned char*>(dtAlloc(t->dataSize * sizeof(unsigned char), DT_ALLOC_PERM));

		if (!data)
		{
			return false;
		}

		memcpy(data, t->data, t->dataSize * sizeof(unsigned char));

		ArMeshTilePtr tile;

		try
		{
			tile = RfNew ArMeshTile(data, t->dataSize, mMesh.backend()->getTileRef(t));
		}
		catch (const std::bad_alloc& e)
		{
			dtFree(data);
			return false;
		}

		if (!obj.addTile(tile))
		{
			return false;
		}
	}

	return true;
}
