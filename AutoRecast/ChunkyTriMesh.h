//
// Copyright (c) 2009-2010 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//
//
// This file is part of RecastDemo, and has been modified by RangerUFO.
//

#ifndef CHUNKYTRIMESH_H
#define CHUNKYTRIMESH_H

#include <RecastAlloc.h>	// Added by RangerUFO

struct rcChunkyTriMeshNode
{
	float bmin[2], bmax[2];
	int i, n;
};

struct rcChunkyTriMesh
{
	inline rcChunkyTriMesh() : nodes(0), tris(0) {};
	// Modified by RangerUFO
	// @{
	inline ~rcChunkyTriMesh()
	{
		if (nodes) rcFree(nodes);
		if (tris) rcFree(tris);
	}
	// @}

	rcChunkyTriMeshNode* nodes;
	int nnodes;
	int* tris;
	int ntris;
	int maxTrisPerChunk;
};

// Added by RangerUFO
// @{
rcChunkyTriMesh* rcAllocChunkyTriMesh();
void rcFreeChunkyTriMesh(rcChunkyTriMesh* p);
// @}

/// Creates partitioned triangle mesh (AABB tree),
/// where each node contains at max trisPerChunk triangles.
bool rcCreateChunkyTriMesh(const float* verts, const int* tris, int ntris,
						   int trisPerChunk, rcChunkyTriMesh* cm);

/// Returns the chunk indices which overlap the input rectable.
int rcGetChunksOverlappingRect(const rcChunkyTriMesh* cm, float bmin[2], float bmax[2], int* ids, const int maxIds);

/// Returns the chunk indices which overlap the input segment.
int rcGetChunksOverlappingSegment(const rcChunkyTriMesh* cm, float p[2], float q[2], int* ids, const int maxIds);


#endif // CHUNKYTRIMESH_H
