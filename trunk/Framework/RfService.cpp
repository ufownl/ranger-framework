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

#include "RfService.h"
#include "System/Timer.h"

RfService::RfService()
	: mInitTime(0)
	, mTickTime(0)
	, mIsInitialized(false)
	, mManager(0)
{
}

RfService::~RfService()
{
}

bool RfService::tick()
{
	unsigned int t = RfClock();

	if (!mIsInitialized)
	{
		if (!onInitialize())
		{
			return false;
		}

		mIsInitialized = true;
	}

	bool ret = onTick(RfClock() - mInitTime);

	mTickTime = RfClock() - t;

	return ret;
}

void RfService::shutdown()
{
	onShutdown();
}

bool RfService::onInitialize()
{
	mInitTime = RfClock();
	mTickTime = 0;
	return true;
}

bool RfService::onTick(long escape)
{
	return true;
}

void RfService::onShutdown()
{
	mIsInitialized = false;
}

long RfService::getInitTime() const
{
	return mInitTime;
}

long RfService::getTickTime() const
{
	return mTickTime;
}

RfServiceManager* RfService::getManager() const
{
	return mManager;
}
