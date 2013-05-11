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

#ifndef __BehaviorTree_BtDecoratorUntilNode_H__
#define __BehaviorTree_BtDecoratorUntilNode_H__

#include "BtNode.h"

class BtDecoratorUntilNode : public BtNode
{
public:
	VISITABLE_DECL(BtGenerator)

public:
	BtDecoratorUntilNode();
	virtual ~BtDecoratorUntilNode();

	void setResult(bool res);
	void setCount(long cnt);

	virtual bool execute(BtParams* params);

private:
	bool mResult;
	long mCount;
};

DeclareSmartPointer(BtDecoratorUntilNode);

template <>
struct BtNodeTraits<BtDecoratorUntilNode>
{
	static const char* name()
	{
		return "BtDecoratorUntilNode";
	}
};

#endif  // __BehaviorTree_BtDecoratorUntilNode_H__
