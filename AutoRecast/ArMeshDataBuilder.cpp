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

#include "ArMeshDataBuilder.h"
#include "InputGeom.h"
#include <Recast.h>
#include <DetourCommon.h>
#include <DetourNavMeshBuilder.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdexcept>

ArMeshDataBuilder::ArMeshDataBuilder(rcContext* ctx, const InputGeom* geom, ArMeshProcess proc /* = 0 */)
	: mContext(ctx)
	, mGeom(geom)
	, mProc(proc)
	, mCellSize(0.3f)
	, mCellHeight(0.2f)
	, mTileSize(32)
	, mAgentHeight(2.0f)
	, mAgentRadius(0.6f)
	, mAgentMaxClimb(0.9f)
	, mAgentMaxSlope(45.0f)
	, mRegionMinSize(8.0f)
	, mRegionMergeSize(20.0f)
	, mMonotonePartition(false)
	, mEdgeMaxLen(12.0f)
	, mEdgeMaxError(1.3f)
	, mVertsPerPoly(6)
	, mDetailSampleDist(6.0f)
	, mDetailSampleMaxError(1.0f)
{
	if (!ctx)
	{
		throw std::invalid_argument("Invalid ctx.");
	}
}

ArMeshDataPtr ArMeshDataBuilder::build(bool buildTiles /* = true */, int* otw /* = 0 */, int* oth /* = 0 */)
{
	if (!mGeom || !mGeom->getMesh())
	{
		mContext->log(RC_LOG_ERROR, "No vertices and triangles.");
		return 0;
	}

	const float* bmin = mGeom->getMeshBoundsMin();
	const float* bmax = mGeom->getMeshBoundsMax();
	int gw = 0;
	int gh = 0;

	rcCalcGridSize(bmin, bmax, mCellSize, &gw, &gh);

	int ts = mTileSize;
	int tw = (gw + ts - 1) / ts;
	int th = (gh + ts - 1) / ts;

	if (otw)
	{
		*otw = tw;
	}

	if (oth)
	{
		*oth = th;
	}

	int tileBits = rcMin(static_cast<int>(dtIlog2(dtNextPow2(tw * th))), 14);
	int polyBits = 22 - tileBits;
	int maxTiles = 1 << tileBits;
	int maxPolysPerTile = 1 << polyBits;

	mContext->log(RC_LOG_PROGRESS, "Max Tiles: %d", maxTiles);
	mContext->log(RC_LOG_PROGRESS, "Max Polys: %d", maxPolysPerTile);

	dtNavMeshParams params;

	rcVcopy(params.orig, mGeom->getMeshBoundsMin());
	params.tileWidth = mTileSize * mCellSize;
	params.tileHeight = mTileSize * mCellSize;
	params.maxTiles = maxTiles;
	params.maxPolys = maxPolysPerTile;

	ArMeshData* data = 0;

	try
	{
		data = RfNew ArMeshData(params);
	}
	catch (const std::bad_alloc& e)
	{
		mContext->log(RC_LOG_ERROR, "Could not allocate ArMeshData.");
		return 0;
	}

	if (buildTiles)
	{
		for (int y = 0; y < th; ++y)
		{
			for (int x = 0; x < tw; ++x)
			{
				int accTime = mContext->getAccumulatedTime(RC_TIMER_TOTAL);

				data->addTile(buildTile(x, y));

				mContext->log(RC_LOG_PROGRESS, " - Build time: %d ms"
						, mContext->getAccumulatedTime(RC_TIMER_TOTAL) - (accTime < 0 ? 0 : accTime));
			}
		}
	}

	return data;
}

ArMeshTilePtr ArMeshDataBuilder::buildTile(int tx, int ty)
{
	if (!mGeom || !mGeom->getMesh() || !mGeom->getChunkyMesh())
	{
		mContext->log(RC_LOG_ERROR, "Input mesh is not specified.");
		return 0;
	}

	const float* verts = mGeom->getMesh()->getVerts();
	int nverts = mGeom->getMesh()->getVertCount();
	int ntris = mGeom->getMesh()->getTriCount();
	const rcChunkyTriMesh* chunkyMesh = mGeom->getChunkyMesh();
	const float* bmin = mGeom->getMeshBoundsMin();
	const float* bmax = mGeom->getMeshBoundsMax();
	float tcs = mTileSize * mCellSize;
	float tileBmin[3] = {bmin[0] + tx * tcs, bmin[1], bmin[2] + ty * tcs};
	float tileBmax[3] = {bmin[0] + (tx + 1) * tcs, bmax[1], bmin[2] + (ty + 1) * tcs};

	rcConfig cfg;

	memset(&cfg, 0, sizeof(cfg));
	cfg.cs = mCellSize;
	cfg.ch = mCellHeight;
	cfg.walkableSlopeAngle = mAgentMaxSlope;
	cfg.walkableHeight = static_cast<int>(ceilf(mAgentHeight / cfg.ch));
	cfg.walkableClimb = static_cast<int>(floorf(mAgentMaxClimb / cfg.ch));
	cfg.walkableRadius = static_cast<int>(ceilf(mAgentRadius / cfg.cs));
	cfg.maxEdgeLen = static_cast<int>(mEdgeMaxLen / cfg.cs);
	cfg.maxSimplificationError = mEdgeMaxError;
	cfg.minRegionArea = static_cast<int>(rcSqr(mRegionMinSize));
	cfg.mergeRegionArea = static_cast<int>(rcSqr(mRegionMergeSize));
	cfg.maxVertsPerPoly = mVertsPerPoly;
	cfg.tileSize = mTileSize;
	cfg.borderSize = cfg.walkableRadius + 3;
	cfg.width = cfg.tileSize + cfg.borderSize * 2;
	cfg.height = cfg.tileSize + cfg.borderSize * 2;
	cfg.detailSampleDist = (mDetailSampleDist < 0.9f ? 0 : mCellSize * mDetailSampleDist);
	cfg.detailSampleMaxError = mCellHeight * mDetailSampleMaxError;
	rcVcopy(cfg.bmin, tileBmin);
	rcVcopy(cfg.bmax, tileBmax);
	cfg.bmin[0] -= cfg.borderSize * cfg.cs;
	cfg.bmin[2] -= cfg.borderSize * cfg.cs;
	cfg.bmax[0] += cfg.borderSize * cfg.cs;
	cfg.bmax[2] += cfg.borderSize * cfg.cs;

	mContext->startTimer(RC_TIMER_TOTAL);

	mContext->log(RC_LOG_PROGRESS, "Building navigation tile[%d, %d]:", tx, ty);
	mContext->log(RC_LOG_PROGRESS, " - %d x %d cells", cfg.width, cfg.height);
	mContext->log(RC_LOG_PROGRESS, " - %.1fK verts, %.1fK tris", nverts / 1000.0f, ntris / 1000.0f);

	rcHeightfield* solid = rcAllocHeightfield();

	if (!solid)
	{
		mContext->log(RC_LOG_ERROR, "Out of memory solid.");
		mContext->stopTimer(RC_TIMER_TOTAL);
		return 0;
	}

	if (!rcCreateHeightfield(mContext, *solid, cfg.width, cfg.height, cfg.bmin, cfg.bmax, cfg.cs, cfg.ch))
	{
		mContext->log(RC_LOG_ERROR, "Could not create solid heightfield.");
		rcFreeHeightField(solid);
		mContext->stopTimer(RC_TIMER_TOTAL);
		return 0;
	}

	unsigned char* triareas
		= static_cast<unsigned char*>(rcAlloc(chunkyMesh->maxTrisPerChunk * sizeof(unsigned char), RC_ALLOC_PERM));

	if (!triareas)
	{
		mContext->log(RC_LOG_ERROR, "Out of memory triareas.");
		rcFreeHeightField(solid);
		mContext->stopTimer(RC_TIMER_TOTAL);
		return 0;
	}

	float tbmin[2] = {cfg.bmin[0], cfg.bmin[2]};
	float tbmax[2] = {cfg.bmax[0], cfg.bmax[2]};
	int cid[512];
	int ncid = rcGetChunksOverlappingRect(chunkyMesh, tbmin, tbmax, cid, 512);

	if (!ncid)
	{
		rcFree(triareas);
		rcFreeHeightField(solid);
		mContext->stopTimer(RC_TIMER_TOTAL);
		return 0;
	}

	for (int i = 0; i < ncid; ++i)
	{
		const rcChunkyTriMeshNode& node = chunkyMesh->nodes[cid[i]];
		const int* ctris = &chunkyMesh->tris[node.i * 3];
		int nctris = node.n;

		memset(triareas, 0, nctris * sizeof(unsigned char));
		rcMarkWalkableTriangles(mContext, cfg.walkableSlopeAngle, verts, nverts, ctris, nctris, triareas);
		rcRasterizeTriangles(mContext, verts, nverts, ctris, triareas, nctris, *solid, cfg.walkableClimb);
	}

	rcFree(triareas);

	rcFilterLowHangingWalkableObstacles(mContext, cfg.walkableClimb, *solid);
	rcFilterLedgeSpans(mContext, cfg.walkableHeight, cfg.walkableClimb, *solid);
	rcFilterWalkableLowHeightSpans(mContext, cfg.walkableHeight, *solid);

	rcCompactHeightfield* chf = rcAllocCompactHeightfield();

	if (!chf)
	{
		mContext->log(RC_LOG_ERROR, "Out of memory chf.");
		rcFreeHeightField(solid);
		mContext->stopTimer(RC_TIMER_TOTAL);
		return 0;
	}

	if (!rcBuildCompactHeightfield(mContext, cfg.walkableHeight, cfg.walkableClimb, *solid, *chf))
	{
		mContext->log(RC_LOG_ERROR, "Could not build compact data.");
		rcFreeCompactHeightfield(chf);
		rcFreeHeightField(solid);
		mContext->stopTimer(RC_TIMER_TOTAL);
		return 0;
	}

	rcFreeHeightField(solid);

	if (!rcErodeWalkableArea(mContext, cfg.walkableRadius, *chf))
	{
		mContext->log(RC_LOG_ERROR, "Could not erode.");
		rcFreeCompactHeightfield(chf);
		mContext->stopTimer(RC_TIMER_TOTAL);
		return 0;
	}

	const ConvexVolume* vols = mGeom->getConvexVolumes();

	for (int i = 0; i < mGeom->getConvexVolumeCount(); ++i)
	{
		rcMarkConvexPolyArea(mContext, vols[i].verts, vols[i].nverts
				, vols[i].hmin, vols[i].hmax, static_cast<unsigned char>(vols[i].area), *chf);
	}

	if (mMonotonePartition)
	{
		if (!rcBuildRegionsMonotone(mContext, *chf, cfg.borderSize, cfg.minRegionArea, cfg.mergeRegionArea))
		{
			mContext->log(RC_LOG_ERROR, "Could not build regions.");
			rcFreeCompactHeightfield(chf);
			mContext->stopTimer(RC_TIMER_TOTAL);
			return 0;
		}
	}
	else
	{
		if (!rcBuildDistanceField(mContext, *chf))
		{
			mContext->log(RC_LOG_ERROR, "Could not build distance field.");
			rcFreeCompactHeightfield(chf);
			mContext->stopTimer(RC_TIMER_TOTAL);
			return 0;
		}

		if (!rcBuildRegions(mContext, *chf, cfg.borderSize, cfg.minRegionArea, cfg.mergeRegionArea))
		{
			mContext->log(RC_LOG_ERROR, "Could not build regions.");
			rcFreeCompactHeightfield(chf);
			mContext->stopTimer(RC_TIMER_TOTAL);
			return 0;
		}
	}

	rcContourSet* cset = rcAllocContourSet();

	if (!cset)
	{
		mContext->log(RC_LOG_ERROR, "Out of memory cset.");
		rcFreeCompactHeightfield(chf);
		mContext->stopTimer(RC_TIMER_TOTAL);
		return 0;
	}

	if (!rcBuildContours(mContext, *chf, cfg.maxSimplificationError, cfg.maxEdgeLen, *cset))
	{
		mContext->log(RC_LOG_ERROR, "Could not create contours.");
		rcFreeContourSet(cset);
		rcFreeCompactHeightfield(chf);
		mContext->stopTimer(RC_TIMER_TOTAL);
		return 0;
	}

	if (!cset->nconts)
	{
		rcFreeContourSet(cset);
		rcFreeCompactHeightfield(chf);
		mContext->stopTimer(RC_TIMER_TOTAL);
		return 0;
	}

	rcPolyMesh* pmesh = rcAllocPolyMesh();

	if (!pmesh)
	{
		mContext->log(RC_LOG_ERROR, "Out of memory pmesh.");
		rcFreeContourSet(cset);
		rcFreeCompactHeightfield(chf);
		mContext->stopTimer(RC_TIMER_TOTAL);
		return 0;
	}

	if (!rcBuildPolyMesh(mContext, *cset, cfg.maxVertsPerPoly, *pmesh))
	{
		mContext->log(RC_LOG_ERROR, "Could not triangulate contours.");
		rcFreePolyMesh(pmesh);
		rcFreeContourSet(cset);
		rcFreeCompactHeightfield(chf);
		mContext->stopTimer(RC_TIMER_TOTAL);
		return 0;
	}

	rcPolyMeshDetail* dmesh = rcAllocPolyMeshDetail();

	if (!dmesh)
	{
		mContext->log(RC_LOG_ERROR, "Out of memory dmesh.");
		rcFreePolyMesh(pmesh);
		rcFreeContourSet(cset);
		rcFreeCompactHeightfield(chf);
		mContext->stopTimer(RC_TIMER_TOTAL);
		return 0;
	}

	if (!rcBuildPolyMeshDetail(mContext, *pmesh, *chf, cfg.detailSampleDist, cfg.detailSampleMaxError, *dmesh))
	{
		mContext->log(RC_LOG_ERROR, "Could build polymesh detail.");
		rcFreePolyMeshDetail(dmesh);
		rcFreePolyMesh(pmesh);
		rcFreeContourSet(cset);
		rcFreeCompactHeightfield(chf);
		mContext->stopTimer(RC_TIMER_TOTAL);
		return 0;
	}

	rcFreeContourSet(cset);
	rcFreeCompactHeightfield(chf);

	if (cfg.maxVertsPerPoly > DT_VERTS_PER_POLYGON)
	{
		mContext->log(RC_LOG_ERROR, "Too many vertices per poly %d (max: %d).", cfg.maxVertsPerPoly, DT_VERTS_PER_POLYGON);
		rcFreePolyMeshDetail(dmesh);
		rcFreePolyMesh(pmesh);
		mContext->stopTimer(RC_TIMER_TOTAL);
		return 0;
	}

	if (pmesh->nverts >= 0xFFFF)
	{
		mContext->log(RC_LOG_ERROR, "Too many vertices per tile %d (max: %d).", pmesh->nverts, 0xFFFF);
		rcFreePolyMeshDetail(dmesh);
		rcFreePolyMesh(pmesh);
		mContext->stopTimer(RC_TIMER_TOTAL);
		return 0;
	}

	if (mProc)
	{
		mProc(pmesh->areas, pmesh->flags, pmesh->npolys);
	}

	dtNavMeshCreateParams params;

	memset(&params, 0, sizeof(params));
	params.verts = pmesh->verts;
	params.vertCount = pmesh->nverts;
	params.polys = pmesh->polys;
	params.polyAreas = pmesh->areas;
	params.polyFlags = pmesh->flags;
	params.polyCount = pmesh->npolys;
	params.nvp = pmesh->nvp;
	params.detailMeshes = dmesh->meshes;
	params.detailVerts = dmesh->verts;
	params.detailVertsCount = dmesh->nverts;
	params.detailTris = dmesh->tris;
	params.detailTriCount = dmesh->ntris;
	params.offMeshConVerts = mGeom->getOffMeshConnectionVerts();
	params.offMeshConRad = mGeom->getOffMeshConnectionRads();
	params.offMeshConDir = mGeom->getOffMeshConnectionDirs();
	params.offMeshConAreas = mGeom->getOffMeshConnectionAreas();
	params.offMeshConFlags = mGeom->getOffMeshConnectionFlags();
	params.offMeshConUserID = mGeom->getOffMeshConnectionId();
	params.offMeshConCount = mGeom->getOffMeshConnectionCount();
	params.walkableHeight = mAgentHeight;
	params.walkableRadius = mAgentRadius;
	params.walkableClimb = mAgentMaxClimb;
	params.tileX = tx;
	params.tileY = ty;
	params.tileLayer = 0;
	rcVcopy(params.bmin, pmesh->bmin);
	rcVcopy(params.bmax, pmesh->bmax);
	params.cs = cfg.cs;
	params.ch = cfg.ch;
	params.buildBvTree = true;

	unsigned char* navData = 0;
	int navDataSize = 0;

	if (!dtCreateNavMeshData(&params, &navData, &navDataSize))
	{
		mContext->log(RC_LOG_ERROR, "Could not build Detour navmesh.");
		rcFreePolyMeshDetail(dmesh);
		rcFreePolyMesh(pmesh);
		mContext->stopTimer(RC_TIMER_TOTAL);
		return 0;
	}

	mContext->log(RC_LOG_PROGRESS, " - Polymesh: %d vertices  %d polygons", pmesh->nverts, pmesh->npolys);

	rcFreePolyMeshDetail(dmesh);
	rcFreePolyMesh(pmesh);

	ArMeshTile* tile = 0;

	try
	{
		tile = RfNew ArMeshTile(navData, navDataSize);
	}
	catch (const std::bad_alloc& e)
	{
		mContext->log(RC_LOG_ERROR, "Could not allocate ArMeshTile.");
		mContext->stopTimer(RC_TIMER_TOTAL);
		return 0;
	}

	mContext->stopTimer(RC_TIMER_TOTAL);

	return tile;
}

rcContext* ArMeshDataBuilder::getContext() const
{
	return mContext;
}

const InputGeom* ArMeshDataBuilder::getInputGeom() const
{
	return mGeom;
}

ArMeshProcess ArMeshDataBuilder::getMeshProcess() const
{
	return mProc;
}

void ArMeshDataBuilder::setCellSize(float val)
{
	mCellSize = val;
}

void ArMeshDataBuilder::setCellHeight(float val)
{
	mCellHeight = val;
}

void ArMeshDataBuilder::setTileSize(int val)
{
	mTileSize = val;
}

void ArMeshDataBuilder::setAgentHeight(float val)
{
	mAgentHeight = val;
}

void ArMeshDataBuilder::setAgentRadius(float val)
{
	mAgentRadius = val;
}

void ArMeshDataBuilder::setAgentMaxClimb(float val)
{
	mAgentMaxClimb = val;
}

void ArMeshDataBuilder::setAgentMaxSlope(float val)
{
	mAgentMaxSlope = val;
}

void ArMeshDataBuilder::setRegionMinSize(float val)
{
	mRegionMinSize = val;
}

void ArMeshDataBuilder::setRegionMergeSize(float val)
{
	mRegionMergeSize = val;
}

void ArMeshDataBuilder::setMonotonePartition(bool val)
{
	mMonotonePartition = val;
}

void ArMeshDataBuilder::setEdgeMaxLen(float val)
{
	mEdgeMaxLen = val;
}

void ArMeshDataBuilder::setEdgeMaxError(float val)
{
	mEdgeMaxError = val;
}

void ArMeshDataBuilder::setVertsPerPoly(int val)
{
	mVertsPerPoly = val;
}

void ArMeshDataBuilder::setDetailSampleDist(float val)
{
	mDetailSampleDist = val;
}

void ArMeshDataBuilder::setDetailSampleMaxError(float val)
{
	mDetailSampleMaxError = val;
}

float ArMeshDataBuilder::getCellSize() const
{
	return mCellSize;
}

float ArMeshDataBuilder::getCellHeight() const
{
	return mCellHeight;
}

int ArMeshDataBuilder::getTileSize() const
{
	return mTileSize;
}

float ArMeshDataBuilder::getAgentHeight() const
{
	return mAgentHeight;
}

float ArMeshDataBuilder::getAgentRadius() const
{
	return mAgentRadius;
}

float ArMeshDataBuilder::getAgentMaxClimb() const
{
	return mAgentMaxClimb;
}

float ArMeshDataBuilder::getAgentMaxSlope() const
{
	return mAgentMaxSlope;
}

float ArMeshDataBuilder::getRegionMinSize() const
{
	return mRegionMinSize;
}

float ArMeshDataBuilder::getRegionMergeSize() const
{
	return mRegionMergeSize;
}

bool ArMeshDataBuilder::getMonotonePartition() const
{
	return mMonotonePartition;
}

float ArMeshDataBuilder::getEdgeMaxLen() const
{
	return mEdgeMaxLen;
}

float ArMeshDataBuilder::getEdgeMaxError() const
{
	return mEdgeMaxError;
}

int ArMeshDataBuilder::getVertsPerPoly() const
{
	return mVertsPerPoly;
}

float ArMeshDataBuilder::getDetailSampleDist() const
{
	return mDetailSampleDist;
}

float ArMeshDataBuilder::getDetailSampleMaxError() const
{
	return mDetailSampleMaxError;
}
