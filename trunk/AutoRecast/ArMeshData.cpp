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

#include "ArMeshData.h"
#include <algorithm>

VISITABLE_IMPL(ArMeshData, ArMeshDataSerializer)

ArMeshData::ArMeshData()
	: mCount(0)
{
}

ArMeshData::ArMeshData(const dtNavMeshParams& params)
	: mParams(params)
	, mTiles(params.maxTiles)
	, mCount(0)
{
}

void ArMeshData::init(const dtNavMeshParams& params)
{
	mParams = params;
	mTiles.clear();
	mTiles.resize(params.maxTiles);
	mCount = 0;
}

const dtNavMeshParams& ArMeshData::getParams() const
{
	return mParams;
}

int ArMeshData::getCount() const
{
	return mCount;
}

bool ArMeshData::addTile(ArMeshTilePtr tile)
{
	if (!tile)
	{
		return false;
	}

	if (static_cast<size_t>(mCount) >= mTiles.size())
	{
		return false;
	}

	mTiles[mCount++] = tile;

	return true;
}

void ArMeshData::removeTile(int idx)
{
	if (idx >= mCount)
	{
		return;
	}

	using std::swap;
	swap(mTiles[idx], mTiles[mCount - 1]);
	mTiles[--mCount] = 0;
}

ArMeshTile* ArMeshData::getTile(int idx) const
{
	if (idx >= mCount)
	{
		return 0;
	}

	return mTiles[idx];
}
