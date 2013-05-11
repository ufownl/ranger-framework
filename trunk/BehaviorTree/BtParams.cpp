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

#include "BtParams.h"

BtParams::BtParams(size_t size)
	: mCache(size)
	, mExtra(0)
{
}

void BtParams::setCacheData(size_t idx, const BtCacheValue& val)
{
	if (idx < mCache.size())
	{
		mCache[idx].value = val;
		mCache[idx].cache = true;
	}
}

const BtParams::BtCacheValue* BtParams::getCacheData(size_t idx) const
{
	if (idx >= mCache.size())
	{
		return 0;
	}

	if (!mCache[idx].cache)
	{
		return 0;
	}

	return &mCache[idx].value;
}

void BtParams::resetCacheData()
{
	for (BtCacheTable::iterator i = mCache.begin(); i != mCache.end(); ++i)
	{
		i->cache = false;
	}
}

void BtParams::setExtraData(void* extra)
{
	mExtra = extra;
}

void* BtParams::getExtraData()
{
	return mExtra;
}
