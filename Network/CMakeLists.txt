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

SET(Network_HEADERS
		NwBuffer.h
		NwBufferBase.h
		NwConnection.h
		NwEventDispatcher.h
		NwEventHandler.h
		NwInitializer.h
		NwListener.h
		NwMessageFilter.h
		NwNetService.h
)

SET(Network_SOURCES
		NwBuffer.cpp
		NwBufferBase.cpp
		NwConnection.cpp
		NwEventDispatcher.cpp
		NwEventHandler.cpp
		NwInitializer.cpp
		NwListener.cpp
		NwMessageFilter.cpp
		NwNetService.cpp
)

INCLUDE_DIRECTORIES(
		${CMAKE_CURRENT_SOURCE_DIR}
		${RANGER_SOURCE_DIR}/Utils
		${RANGER_SOURCE_DIR}/Contribs/include
)

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

SET(LIBRARY_OUTPUT_PATH ${RANGER_BINARY_DIR}/lib)

ADD_LIBRARY(Network SHARED
		${Network_HEADERS}
		${Network_SOURCES}
)

ADD_DEPENDENCIES(Network Utils)

LINK_DIRECTORIES(${RANGER_SOURCE_DIR}/Contribs/lib)

IF(WIN32)
	TARGET_LINK_LIBRARIES(Network Utils event_core)
ELSE(WIN32)
	TARGET_LINK_LIBRARIES(Network Utils event_core event_pthreads)
ENDIF(WIN32)

INSTALL(TARGETS Network DESTINATION lib)
INSTALL(FILES ${Network_HEADERS} DESTINATION include)
