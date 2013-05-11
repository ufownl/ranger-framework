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

#include "RfAction.h"
#include "RfActionHandler.h"

RfAction::RfAction()
	: mActionID(-1)
	, mHandler(0)
	, mIsActive(false)
	, mTimeout(-1)
{
}

RfAction::~RfAction()
{
}

void RfAction::setHandler(RfActionHandler* handler)
{
	mHandler = handler;
}

void RfAction::setTimeout(long timeout)
{
	mTimeout = timeout;
}

bool RfAction::execute()
{
	if (onExecute())
	{
		if (!mHandler->insert(this))
		{
			return false;
		}

		mIsActive = true;
		tick();
	}

	return true;
}

RfAction::ID RfAction::id() const
{
	return mActionID;
}

void RfAction::response(const void* params)
{
	if (onResponse(params))
	{
		mIsActive = false;
		mHandler->remove(this);
	}
}

bool RfAction::onResponse(const void* params)
{
	return true;
}

bool RfAction::onTick(long escape)
{
	if (!RfService::onTick(escape))
	{
		return false;
	}

	if (!mIsActive)
	{
		return false;
	}

	if (escape >= mTimeout)
	{
		response(0);
		return false;
	}

	if (mTimeout >= 0)
	{
		mHandler->mActTick.push(this);
	}

	return true;
}
