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

#include "InputGeom.h"
#include "ArMeshDataBuilder.h"
#include "ArMeshDataFileWriter.h"
#include "ArMeshDataFileReader.h"
#include "ArMesh.h"
#include "ArMeshImporter.h"
#include "ArMeshExporter.h"
#include "ArQuery.h"
#include "System/Timer.h"
#include <Recast.h>
#include <stdio.h>

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define Sample_Alloc	TCMallocAllocator
#else
#define Sample_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

template <class T>
static void* allocCustom(int size, T)
{
#ifdef _DEBUG
	return Sample_Alloc::allocate(size, __FILE__, __LINE__);
#else
	return Sample_Alloc::allocate(size);
#endif  // _DEBUG
}

static void freeCustom(void* p)
{
	Sample_Alloc::deallocate(p);
}

class BuildContext : public rcContext
{
public:
	BuildContext()
	{
		resetTimers();
	}

protected:
	virtual void doLog(const rcLogCategory category, const char* msg, const int)
	{
		switch (category)
		{
		case RC_LOG_WARNING:
			printf("warning: ");
			break;
		case RC_LOG_ERROR:
			printf("error: ");
			break;
		}

		puts(msg);
	}

	virtual void doResetTimers()
	{
		for (int i = 0; i < RC_MAX_TIMERS; ++i)
		{
			mAccTime[i] = -1;
		}
	}

	virtual void doStartTimer(const rcTimerLabel label)
	{
		if (label >= RC_MAX_TIMERS)
		{
			return;
		}

		mStartTime[label] = RfClock();
	}

	virtual void doStopTimer(const rcTimerLabel label)
	{
		if (label >= RC_MAX_TIMERS)
		{
			return;
		}

		int delta = RfClock() - mStartTime[label];

		if (mAccTime[label] == -1)
		{
			mAccTime[label] = delta;
		}
		else
		{
			mAccTime[label] += delta;
		}
	}

	virtual int doGetAccumulatedTime(const rcTimerLabel label) const
	{
		if (label >= RC_MAX_TIMERS)
		{
			return -1;
		}

		return mAccTime[label];
	}

private:
	int mStartTime[RC_MAX_TIMERS];
	int mAccTime[RC_MAX_TIMERS];
};

enum SamplePolyAreas
{
	SAMPLE_POLYAREA_GROUND,
	SAMPLE_POLYAREA_WATER,
	SAMPLE_POLYAREA_ROAD,
	SAMPLE_POLYAREA_DOOR,
	SAMPLE_POLYAREA_GRASS,
	SAMPLE_POLYAREA_JUMP,
};

enum SamplePolyFlags
{
	SAMPLE_POLYFLAGS_WALK		= 0x01,
	SAMPLE_POLYFLAGS_SWIM		= 0x02,
	SAMPLE_POLYFLAGS_DOOR		= 0x04,
	SAMPLE_POLYFLAGS_JUMP		= 0x08,
	SAMPLE_POLYFLAGS_DISABLED	= 0x10,
	SAMPLE_POLYFLAGS_ALL		= 0xffff
};

void meshProcess(unsigned char* areas, unsigned short* flags, int npolys)
{
	for (int i = 0; i < npolys; ++i)
	{
		if (areas[i] == RC_WALKABLE_AREA)
		{
			areas[i] = SAMPLE_POLYAREA_GROUND;
		}
		
		switch (areas[i])
		{
		case SAMPLE_POLYAREA_GROUND:
		case SAMPLE_POLYAREA_GRASS:
		case SAMPLE_POLYAREA_ROAD:
			flags[i] = SAMPLE_POLYFLAGS_WALK;
			break;
		case SAMPLE_POLYAREA_WATER:
			flags[i] = SAMPLE_POLYFLAGS_SWIM;
			break;
		case SAMPLE_POLYAREA_DOOR:
			flags[i] = SAMPLE_POLYFLAGS_WALK | SAMPLE_POLYFLAGS_DOOR;
			break;
		}
	}
}

bool save(rcContext* ctx, ArMeshData* data)
{
	FILE* out = fopen("./all_tiles_navmesh.bin", "wb");

	if (!out)
	{
		ctx->log(RC_LOG_ERROR, "Open all_tiles_navmesh.bin failed.");
		return false;
	}

	ArMeshDataFileWriter writer(out);

	if (!writer.serialize(*data))
	{
		ctx->log(RC_LOG_ERROR, "Write ArMeshData failed.");
		fclose(out);
		return false;
	}

	fclose(out);

	return true;
}

bool exportMesh(rcContext* ctx, const ArMesh& mesh)
{
	ArMeshData data;
	ArMeshExporter exporter(mesh);

	if (!exporter.serialize(data))
	{
		ctx->log(RC_LOG_ERROR, "Export ArMeshData failed.");
		return false;
	}

	if (!save(ctx, &data))
	{
		return false;
	}

	return true;
}

int main()
{
	rcAllocSetCustom(allocCustom<rcAllocHint>, freeCustom);
	dtAllocSetCustom(allocCustom<dtAllocHint>, freeCustom);

	BuildContext ctx;
	InputGeom geom;

	geom.load(&ctx, "./geomset.txt");

	ArMeshDataBuilder builder(&ctx, &geom, meshProcess);

	builder.setAgentMaxClimb(1.8f);

	ArMeshDataPtr data = builder.build();

	if (!data)
	{
		ctx.log(RC_LOG_ERROR, "Build ArMeshData failed.");
		return -1;
	}

	ctx.log(RC_LOG_PROGRESS, "Total build time: %d ms", ctx.getAccumulatedTime(RC_TIMER_TOTAL));

	if (!save(&ctx, data))
	{
		return -1;
	}

	FILE* in = fopen("./all_tiles_navmesh.bin", "rb");

	if (!in)
	{
		ctx.log(RC_LOG_ERROR, "Open all_tiles_navmesh.bin failed.");
		return -1;
	}

	ArMeshDataFileReader reader(in);

	if (!reader.serialize(*data))
	{
		ctx.log(RC_LOG_ERROR, "Read ArMeshData failed.");
		fclose(in);
		return -1;
	}

	fclose(in);

	ArMesh mesh;
	ArMeshImporter importer(mesh);

	if (!importer.serialize(*data))
	{
		ctx.log(RC_LOG_ERROR, "Import ArMeshData failed.");
		return -1;
	}
	
	ArQuery query;

	if (dtStatusFailed(query.init(&mesh, 2048)))
	{
		ctx.log(RC_LOG_ERROR, "Init ArQuery failed.");
		return -1;
	}

	float sp[3];
	
	printf("start: ");
	scanf("%f%f%f", sp, sp + 1, sp + 2);

	float ep[3];

	printf("end:   ");
	scanf("%f%f%f", ep, ep + 1, ep + 2);

	float ext[3] = {2, 4, 2};
	dtQueryFilter filter;

	filter.setAreaCost(SAMPLE_POLYAREA_GROUND, 1.0f);
	filter.setAreaCost(SAMPLE_POLYAREA_WATER, 10.0f);
	filter.setAreaCost(SAMPLE_POLYAREA_ROAD, 1.0f);
	filter.setAreaCost(SAMPLE_POLYAREA_DOOR, 1.0f);
	filter.setAreaCost(SAMPLE_POLYAREA_GRASS, 2.0f);
	filter.setAreaCost(SAMPLE_POLYAREA_JUMP, 1.5f);

	dtPolyRef sr;

	query.backend()->findNearestPoly(sp, ext, &filter, &sr, 0);

	dtPolyRef er;

	query.backend()->findNearestPoly(ep, ext, &filter, &er, 0);

	dtPolyRef polys[256];
	int npolys;

	query.backend()->findPath(sr, er, sp, ep, &filter, polys, &npolys, 256);

	float path[256 * 3];
	dtPolyRef pathPolys[256];
	unsigned char pathFlags[256];
	int pathLen;

	query.backend()->findStraightPath(sp, ep, polys, npolys, path, pathFlags, pathPolys, &pathLen, 256, 0);

	printf("path:\n%d\n", pathLen);

	for (int i = 0; i < pathLen; ++i)
	{
		printf("%f %f %f\n", path[i * 3], path[i * 3 + 1], path[i * 3 + 2]);
	}

	if (!exportMesh(&ctx, mesh))
	{
		return -1;
	}

	return 0;
}
