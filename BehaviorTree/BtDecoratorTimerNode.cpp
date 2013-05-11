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

#include "BtDecoratorTimerNode.h"
#include "BtParams.h"
#include <time.h>

static BtNodeFactoryRegister<BtDecoratorTimerNode> msReg;

VISITABLE_IMPL(BtDecoratorTimerNode, BtGenerator)

BtDecoratorTimerNode::BtDecoratorTimerNode()
	: mCooldown(0.0f)
	, mIndex(-1)
{
}

BtDecoratorTimerNode::~BtDecoratorTimerNode()
{
}

void BtDecoratorTimerNode::setCooldown(float cd)
{
	mCooldown = cd;
}

void BtDecoratorTimerNode::setIndex(size_t idx)
{
	mIndex = idx;
}

bool BtDecoratorTimerNode::execute(BtParams* params)
{
	BtNode* node = getFirstChild();

	if (!node)
	{
		return false;
	}

	const BtParams::BtCacheValue* p = params->getCacheData(mIndex);

	if (p && clock() - p->long_v < mCooldown * CLOCKS_PER_SEC)
	{
		return false;
	}

	if (!node->execute(params))
	{
		return false;
	}

	BtParams::BtCacheValue v;

	v.long_v = clock();
	params->setCacheData(mIndex, v);

	return true;
}
