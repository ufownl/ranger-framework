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

#include "BtDecoratorUntilNode.h"

VISITABLE_IMPL(BtDecoratorUntilNode, BtGenerator)

BtDecoratorUntilNode::BtDecoratorUntilNode()
	: mResult(false)
	, mCount(-1)
{
}

BtDecoratorUntilNode::~BtDecoratorUntilNode()
{
}

void BtDecoratorUntilNode::setResult(bool res)
{
	mResult = res;
}

void BtDecoratorUntilNode::setCount(long cnt)
{
	mCount = cnt;
}

bool BtDecoratorUntilNode::execute(BtParams* params)
{
	BtNode* node = getFirstChild();

	if (!node)
	{
		return false;
	}

	for (long i = 0; mCount < 0 || i < mCount; ++i)
	{
		if (node->execute(params) == mResult)
		{
			return true;
		}
	}

	return false;
}
