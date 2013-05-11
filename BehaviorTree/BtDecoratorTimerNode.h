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

#ifndef __BehaviorTree_BtDecoratorTimerNode_H__
#define __BehaviorTree_BtDecoratorTimerNode_H__

#include "BtNode.h"

class BtDecoratorTimerNode : public BtNode
{
public:
	VISITABLE_DECL(BtGenerator)

public:
	BtDecoratorTimerNode();
	virtual ~BtDecoratorTimerNode();

	void setCooldown(float cd);
	void setIndex(size_t idx);

	virtual bool execute(BtParams* params);

private:
	float mCooldown;
	size_t mIndex;
};

DeclareSmartPointer(BtDecoratorTimerNode);

template <>
struct BtNodeTraits<BtDecoratorTimerNode>
{
	static const char* name()
	{
		return "BtDecoratorTimerNode";
	}
};

#endif  // __BehaviorTree_BtDecoratorTimerNode_H__
