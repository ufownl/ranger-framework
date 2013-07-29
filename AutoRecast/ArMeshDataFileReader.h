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

#ifndef __AutoRecast_ArMeshDataFileReader_H__
#define __AutoRecast_ArMeshDataFileReader_H__

#include "ArMeshDataSerializer.h"
#include <stdio.h>

class ArMeshDataFileReader : public ArMeshDataSerializer
{
public:
	ArMeshDataFileReader(FILE* in);

protected:
	virtual bool onVisit(ArMeshTile& obj);
	virtual bool onVisit(ArMeshData& obj);

private:
	FILE* mIn;
};

DeclareSmartPointer(ArMeshDataFileReader);

#endif  // __AutoRecast_ArMeshDataFileReader_H__
