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

#ifndef __AutoRecast_ArMeshDataBuilder_H__
#define __AutoRecast_ArMeshDataBuilder_H__

#include "ArMeshData.h"
#include <boost/function.hpp>

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define ArMeshDataBuilder_Alloc	TCMallocAllocator
#else
#define ArMeshDataBuilder_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class rcContext;
class InputGeom;

typedef boost::function<
	void(unsigned char*, unsigned short*, int)
> ArMeshProcess;

class ArMeshDataBuilder : public RefObject<ArMeshDataBuilder_Alloc>
{
public:
	ArMeshDataBuilder(rcContext* ctx, const InputGeom* geom, ArMeshProcess proc = 0);

	ArMeshDataPtr build(bool buildTiles = true, int* otw = 0, int* oth = 0);
	ArMeshTilePtr buildTile(int tx, int ty);

	rcContext* getContext() const;
	const InputGeom* getInputGeom() const;
	ArMeshProcess getMeshProcess() const;

	void setCellSize(float val);
	void setCellHeight(float val);
	void setTileSize(int val);
	void setAgentHeight(float val);
	void setAgentRadius(float val);
	void setAgentMaxClimb(float val);
	void setAgentMaxSlope(float val);
	void setRegionMinSize(float val);
	void setRegionMergeSize(float val);
	void setMonotonePartition(bool val);
	void setEdgeMaxLen(float val);
	void setEdgeMaxError(float val);
	void setVertsPerPoly(int val);
	void setDetailSampleDist(float val);
	void setDetailSampleMaxError(float val);

	float getCellSize() const;
	float getCellHeight() const;
	int getTileSize() const;
	float getAgentHeight() const;
	float getAgentRadius() const;
	float getAgentMaxClimb() const;
	float getAgentMaxSlope() const;
	float getRegionMinSize() const;
	float getRegionMergeSize() const;
	bool getMonotonePartition() const;
	float getEdgeMaxLen() const;
	float getEdgeMaxError() const;
	int getVertsPerPoly() const;
	float getDetailSampleDist() const;
	float getDetailSampleMaxError() const;
	
private:
	rcContext* mContext;
	const InputGeom* mGeom;
	ArMeshProcess mProc;

	float mCellSize;
	float mCellHeight;
	int mTileSize;
	float mAgentHeight;
	float mAgentRadius;
	float mAgentMaxClimb;
	float mAgentMaxSlope;
	float mRegionMinSize;
	float mRegionMergeSize;
	bool mMonotonePartition;
	float mEdgeMaxLen;
	float mEdgeMaxError;
	int mVertsPerPoly;
	float mDetailSampleDist;
	float mDetailSampleMaxError;
};

DeclareSmartPointer(ArMeshDataBuilder);

#endif  // __AutoRecast_ArMeshDataBuilder_H__
