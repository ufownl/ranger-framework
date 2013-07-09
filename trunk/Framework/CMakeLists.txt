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

SET(Framework_HEADERS
		RfAction.h
		RfActionHandler.h
		RfRequestService.h
		RfRunnableService.h
		RfService.h
		RfServiceManager.h
)

SET(Framework_SOURCES
		RfAction.cpp
		RfActionHandler.cpp
		RfRequestService.cpp
		RfRunnableService.cpp
		RfService.cpp
		RfServiceManager.cpp
)

INCLUDE_DIRECTORIES(
		.
		${RANGER_SOURCE_DIR}/Utils
)

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

SET(LIBRARY_OUTPUT_PATH ${RANGER_BINARY_DIR}/lib)

ADD_LIBRARY(Framework SHARED
		${Framework_HEADERS}
		${Framework_SOURCES}
)

ADD_DEPENDENCIES(Framework Utils)

TARGET_LINK_LIBRARIES(Framework Utils)

INSTALL(TARGETS Framework DESTINATION lib)
INSTALL(FILES ${Framework_HEADERS} DESTINATION include)
