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

#include "ArMesh.h"
#include "ArMeshTile.h"

ArMesh::ArMesh()
	: mBackend(0)
{
}

ArMesh::~ArMesh()
{
	if (mBackend)
	{
		dtFreeNavMesh(mBackend);
	}
}

dtStatus ArMesh::init(const dtNavMeshParams& params)
{
	if (mBackend)
	{
		dtFreeNavMesh(mBackend);
	}

	mBackend = dtAllocNavMesh();

	if (!mBackend)
	{
		return DT_FAILURE | DT_OUT_OF_MEMORY;
	}

	return mBackend->init(&params);
}

dtStatus ArMesh::addTile(const ArMeshTile* tile, dtTileRef* ref /* = 0 */)
{
	if (!mBackend)
	{
		return DT_FAILURE;
	}

	if (!tile || !tile->getData())
	{
		return DT_FAILURE | DT_INVALID_PARAM;
	}

	return mBackend->addTile(tile->getData(), tile->getSize(), 0, tile->getRef(), ref);
}

dtStatus ArMesh::removeTile(dtTileRef ref)
{
	if (!mBackend)
	{
		return DT_FAILURE;
	}

	return mBackend->removeTile(ref, 0, 0);
}

dtStatus ArMesh::setPolyFlags(dtPolyRef ref, unsigned short flags)
{
	if (!mBackend)
	{
		return DT_FAILURE;
	}

	return mBackend->setPolyFlags(ref, flags);
}

dtStatus ArMesh::setPolyArea(dtPolyRef ref, unsigned char area)
{
	if (!mBackend)
	{
		return DT_FAILURE;
	}

	return mBackend->setPolyArea(ref, area);
}

dtStatus ArMesh::restoreTileState(dtMeshTile* tile, const unsigned char* data, int maxDataSize)
{
	if (!mBackend)
	{
		return DT_FAILURE;
	}

	if (!tile || !data)
	{
		return DT_FAILURE | DT_INVALID_PARAM;
	}

	return mBackend->restoreTileState(tile, data, maxDataSize);
}

const dtNavMesh* ArMesh::backend() const
{
	return mBackend;
}
