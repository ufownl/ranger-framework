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

#include "ArQuery.h"
#include "ArMesh.h"

ArQuery::ArQuery()
	: mBackend(0)
{
}

ArQuery::~ArQuery()
{
	if (mBackend)
	{
		dtFreeNavMeshQuery(mBackend);
	}
}

dtStatus ArQuery::init(const ArMesh* mesh, int maxNodes)
{
	if (!mesh || !mesh->backend() || !maxNodes)
	{
		return DT_FAILURE | DT_INVALID_PARAM;
	}

	if (mBackend)
	{
		dtFreeNavMeshQuery(mBackend);
	}

	mBackend = dtAllocNavMeshQuery();

	if (!mBackend)
	{
		return DT_FAILURE | DT_OUT_OF_MEMORY;
	}

	return mBackend->init(mesh->backend(), maxNodes);
}

dtStatus ArQuery::initSlicedFindPath(dtPolyRef startRef, dtPolyRef endRef
		, const float* startPos, const float* endPos, const dtQueryFilter* filter)
{
	if (!mBackend)
	{
		return DT_FAILURE;
	}

	if (!startRef || !endRef || !startPos || !endPos || !filter)
	{
		return DT_FAILURE | DT_INVALID_PARAM;
	}

	return mBackend->initSlicedFindPath(startRef, endRef, startPos, endPos, filter);
}

dtStatus ArQuery::updateSlicedFindPath(int maxIter, int* doneIters)
{
	if (!mBackend)
	{
		return DT_FAILURE;
	}

	return mBackend->updateSlicedFindPath(maxIter, doneIters);
}

dtStatus ArQuery::finalizeSlicedFindPath(dtPolyRef* path, int* pathCount, int maxPath)
{
	if (!mBackend)
	{
		return DT_FAILURE;
	}

	if (!path || !pathCount)
	{
		return DT_FAILURE | DT_INVALID_PARAM;
	}

	return mBackend->finalizeSlicedFindPath(path, pathCount, maxPath);
}

dtStatus ArQuery::finalizeSlicedFindPathPartial(
		const dtPolyRef* existing, int existingSize, dtPolyRef* path, int* pathCount, int maxPath)
{
	if (!mBackend)
	{
		return DT_FAILURE;
	}

	if (!existing || !path || !pathCount)
	{
		return DT_FAILURE | DT_INVALID_PARAM;
	}

	return mBackend->finalizeSlicedFindPathPartial(existing, existingSize, path, pathCount, maxPath);
}

const dtNavMeshQuery* ArQuery::backend() const
{
	return mBackend;
}
