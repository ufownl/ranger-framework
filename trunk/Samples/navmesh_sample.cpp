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
#include "System/Timer.h"
#include <Recast.h>
#include <stdio.h>

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

	virtual int doGetAccumulatedTime(const rcTimerLabel label)
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

int main()
{
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

	FILE* out = fopen("./all_tiles_navmesh.bin", "wb");

	if (!out)
	{
		ctx.log(RC_LOG_ERROR, "Open all_tiles_navmesh.bin failed.");
		return -1;
	}

	ArMeshDataFileWriter writer(out);

	if (!writer.serialize(*data))
	{
		ctx.log(RC_LOG_ERROR, "Write ArMeshData failed.");
	}

	fclose(out);

	return 0;
}
