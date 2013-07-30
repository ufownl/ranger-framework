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

#include "ArMeshImporter.h"
#include "ArMeshTile.h"
#include "ArMeshData.h"
#include "ArMesh.h"

ArMeshImporter::ArMeshImporter(ArMesh& mesh)
	: mMesh(mesh)
{
}

bool ArMeshImporter::onVisit(ArMeshTile& obj)
{
	return dtStatusSucceed(mMesh.addTile(&obj));
}

bool ArMeshImporter::onVisit(ArMeshData& obj)
{
	if (dtStatusFailed(mMesh.init(obj.getParams())))
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
