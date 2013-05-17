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

#ifndef __RangerFramework_RfActionHandler_H__
#define __RangerFramework_RfActionHandler_H__

#include "RfAction.h"
#include "Memory/STLAllocator.h"
#include "Object/ObjectPool.h"
#include "Container/round_robin_queue.h"

class RfActionHandler : public RfService
{
public:
	friend class RfAction;

public:
	RfActionHandler(size_t maxSize = 0x10000);
	virtual ~RfActionHandler();

	RfAction* get(RfAction::ID id);
	void response(RfAction::ID id, const void* params);

protected:
	virtual bool onTick(long escape);

private:
	bool insert(RfAction* action);
	void remove(RfAction* action);

private:
	struct action_wrapper_t : instrusive_slist_node<action_wrapper_t>
	{
		RfActionPtr action;

		void onDeallocate() { action = 0; }
	};

	typedef ObjectPool<action_wrapper_t, ::SingleThread> RfActionPool;
	typedef round_robin_queue<
		RfActionPtr,
		std::vector<RfActionPtr, stl_alloc<RfActionPtr>::type>
	> RfActionTickQueue;

	RfActionPool mActPool;
	RfActionTickQueue mActTick;
};

DeclareSmartPointer(RfActionHandler);

#endif  // __RangerFramework_RfActionHandler_H__
