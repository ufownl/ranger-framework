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

#include "BtDecoratorCounterNode.h"
#include "BtParams.h"

VISITABLE_IMPL(BtDecoratorCounterNode, BtGenerator)

BtDecoratorCounterNode::BtDecoratorCounterNode()
	: mCount(0)
	, mIndex(-1)
{
}

BtDecoratorCounterNode::~BtDecoratorCounterNode()
{
}

void BtDecoratorCounterNode::setCount(size_t cnt)
{
	mCount = cnt;
}

void BtDecoratorCounterNode::setIndex(size_t idx)
{
	mIndex = idx;
}

bool BtDecoratorCounterNode::execute(BtParams* params)
{
	BtNode* node = getFirstChild();

	if (!node)
	{
		return false;
	}

	const BtParams::BtCacheValue* p = params->getCacheData(mIndex);

	if (p && p->ulong_v >= mCount)
	{
		return false;
	}

	if (!node->execute(params))
	{
		return false;
	}

	BtParams::BtCacheValue v;

	v.ulong_v = (p ? p->ulong_v + 1 : 1);
	params->setCacheData(mIndex, v);

	return true;
}
