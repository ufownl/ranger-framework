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

#include "RfRunnableService.h"
#include "System/Timer.h"

RfRunnableService::RfRunnableService(long period)
	: mPeriod(period)
	, mIsRunning(false)
{
}

RfRunnableService::~RfRunnableService()
{
}

void RfRunnableService::run()
{
	while (tick())
	{
		long t = mPeriod - getTickTime();

		t = (t > 0 ? t : 0);

		if (t)
		{
			RfSleep(t);
		}
	}

	shutdown();
}

void RfRunnableService::stop()
{
	mIsRunning = false;
}

bool RfRunnableService::isRunning()
{
	return mIsRunning;
}

bool RfRunnableService::onInitialize()
{
	if (!RfService::onInitialize())
	{
		return false;
	}

	mIsRunning = true;

	return true;
}

bool RfRunnableService::onTick(long escape)
{
	if (!RfService::onTick(escape))
	{
		return false;
	}

	return isRunning();
}
