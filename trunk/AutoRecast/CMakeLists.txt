#	Copyright 2013 RangerUFO
#
#	This file is part of RangerFramework.
#
#	RangerFramework is free software: you can redistribute it and/or modify
#	it under the terms of the GNU Lesser General Public License as published by
#	the Free Software Foundation, either version 3 of the License, or
#	(at your option) any later version.
#
#	RangerFramework is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU Lesser General Public License for more details.
#
#	You should have received a copy of the GNU Lesser General Public License
#	along with RangerFramework.  If not, see <http://www.gnu.org/licenses/>.

SET(AutoRecast_HEADERS
		MeshLoaderObj.h
		ChunkyTriMesh.h
		InputGeom.h
		ArMeshTile.h
		ArMeshData.h
		ArMeshDataBuilder.h
		ArMeshDataSerializer.h
		ArMeshDataFileWriter.h
		ArMeshDataFileReader.h
)

SET(AutoRecast_SOURCES
		MeshLoaderObj.cpp
		ChunkyTriMesh.cpp
		InputGeom.cpp
		ArMeshTile.cpp
		ArMeshData.cpp
		ArMeshDataBuilder.cpp
		ArMeshDataFileWriter.cpp
		ArMeshDataFileReader.cpp
)

INCLUDE_DIRECTORIES(
		${CMAKE_CURRENT_SOURCE_DIR}
		${RANGER_SOURCE_DIR}/Utils
		${RANGER_SOURCE_DIR}/Contribs/include
)

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

SET(LIBRARY_OUTPUT_PATH ${RANGER_BINARY_DIR}/lib)

ADD_LIBRARY(AutoRecast
		${AutoRecast_HEADERS}
		${AutoRecast_SOURCES}
)

ADD_DEPENDENCIES(AutoRecast Utils)

LINK_DIRECTORIES(${RANGER_SOURCE_DIR}/Contribs/lib)

TARGET_LINK_LIBRARIES(AutoRecast Utils DebugUtils Recast Detour DetourCrowd DetourTileCache)

INSTALL(TARGETS AutoRecast DESTINATION lib)
INSTALL(FILES ${AutoRecast_HEADERS} DESTINATION include)
