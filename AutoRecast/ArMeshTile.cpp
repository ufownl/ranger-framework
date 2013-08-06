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

#include "ArMeshTile.h"

VISITABLE_IMPL(ArMeshTile, ArMeshDataSerializer)

ArMeshTile::ArMeshTile()
	: mData(0)
	, mSize(0)
	, mRef(0)
{
}

ArMeshTile::ArMeshTile(unsigned char* data, int size, dtTileRef ref /* = 0 */)
	: mData(data)
	, mSize(size)
	, mRef(ref)
{
}

ArMeshTile::~ArMeshTile()
{
	clear();
}

void ArMeshTile::init(unsigned char* data, int size, dtTileRef ref /* = 0 */)
{
	clear();

	mData = data;
	mSize = size;
	mRef = ref;
}

unsigned char* ArMeshTile::getData() const
{
	return mData;
}

int ArMeshTile::getSize() const
{
	return mSize;
}

dtTileRef ArMeshTile::getRef() const
{
	return mRef;
}

void ArMeshTile::clear()
{
	if (mData)
	{
		dtFree(mData);
		mData = 0;
	}
}
