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

#include "RfServiceManager.h"

RfServiceManager::RfServiceManager(long period /* = 100 */)
	: RfRunnableService(period)
{
}

RfServiceManager::~RfServiceManager()
{
}

void RfServiceManager::append(RfServicePtr service)
{
	mServices.push_back(service);
}

void RfServiceManager::prepend(RfServicePtr service)
{
	mServices.push_front(service);
}

RfServiceManager::RfServiceList::iterator RfServiceManager::insert(RfServiceList::iterator pos, RfServicePtr service)
{
	return mServices.insert(pos, service);
}

RfServiceManager::RfServiceList::iterator RfServiceManager::remove(RfServiceList::iterator pos)
{
	return mServices.erase(pos);
}

RfServiceManager::RfServiceList::iterator RfServiceManager::nil()
{
	return mServices.end();
}

bool RfServiceManager::onTick(long escape)
{
	if (!RfRunnableService::onTick(escape))
	{
		return false;
	}

	RfServiceList tl(mServices);

	for (RfServiceList::iterator i = tl.begin(); i != tl.end(); ++i)
	{
		if (!(*i)->tick())
		{
			return false;
		}
	}

	return true;
}

void RfServiceManager::onShutdown()
{
	for (RfServiceList::iterator i = mServices.begin(); i != mServices.end(); ++i)
	{
		(*i)->shutdown();
	}
	mServices.clear();
	RfRunnableService::onShutdown();
}
