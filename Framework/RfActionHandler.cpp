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

#include "RfActionHandler.h"

RfActionHandler::RfActionHandler(size_t maxSize /* = 0x10000 */)
	: mActPool(maxSize, 0, &action_wrapper_t::onDeallocate)
	, mActTick(maxSize * 2)
{
}

RfActionHandler::~RfActionHandler()
{
}

RfAction* RfActionHandler::get(RfAction::ID id)
{
	if (id < 0 || static_cast<size_t>(id) >= mActPool.size())
	{
		return 0;
	}

	return (mActPool.pool() + id)->action;
}

void RfActionHandler::response(RfAction::ID id, const void* params)
{
	RfAction* action = get(id);

	if (action)
	{
		action->response(params);
	}
}

bool RfActionHandler::onTick(long escape)
{
	if (!RfService::onTick(escape))
	{
		return false;
	}

	size_t cnt = mActTick.size();

	for (size_t i = 0; i < cnt; ++i)
	{
		mActTick.front()->tick();
		mActTick.front() = 0;
		mActTick.pop();
	}

	return true;
}

bool RfActionHandler::insert(RfActionPtr action)
{
	action_wrapper_t* wrapper = mActPool.allocate();

	if (!wrapper)
	{
		return false;
	}

	action->mActionID = wrapper - mActPool.pool();
	wrapper->action = action;

	return true;
}

void RfActionHandler::remove(RfActionPtr action)
{
	if (action->mActionID < 0 || static_cast<size_t>(action->mActionID) >= mActPool.size())
	{
		return;
	}

	action_wrapper_t* wrapper = mActPool.pool() + action->mActionID;

	if (wrapper->action == action)
	{
		mActPool.deallocate(wrapper);
	}
}
