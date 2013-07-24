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

INCLUDE_DIRECTORIES(
		${CMAKE_CURRENT_SOURCE_DIR}
		${RANGER_SOURCE_DIR}/Utils
		${RANGER_SOURCE_DIR}/Framework
		${RANGER_SOURCE_DIR}/BehaviorTree
		${RANGER_SOURCE_DIR}/Network
		${RANGER_SOURCE_DIR}/Contribs/include
)

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

ADD_EXECUTABLE(bt_sample bt_sample.cpp)
ADD_EXECUTABLE(coroutine_sample coroutine_sample.cpp)
ADD_EXECUTABLE(factory_sample factory_sample.cpp)
ADD_EXECUTABLE(framework_sample framework_sample.cpp)
ADD_EXECUTABLE(fsm_sample fsm_sample.cpp)
ADD_EXECUTABLE(multimethods_sample multimethods_sample.cpp)
ADD_EXECUTABLE(network_sample network_sample.cpp)
ADD_EXECUTABLE(visitor_sample visitor_sample.cpp)

ADD_DEPENDENCIES(bt_sample Utils BehaviorTree)
ADD_DEPENDENCIES(coroutine_sample Utils)
ADD_DEPENDENCIES(factory_sample Utils)
ADD_DEPENDENCIES(framework_sample Utils Framework)
ADD_DEPENDENCIES(fsm_sample Utils)
ADD_DEPENDENCIES(multimethods_sample Utils)
ADD_DEPENDENCIES(network_sample Utils Network)
ADD_DEPENDENCIES(visitor_sample Utils)

LINK_DIRECTORIES(${RANGER_SOURCE_DIR}/Contribs/lib)

TARGET_LINK_LIBRARIES(bt_sample BehaviorTree Utils)
TARGET_LINK_LIBRARIES(coroutine_sample Utils)
TARGET_LINK_LIBRARIES(factory_sample Utils)
TARGET_LINK_LIBRARIES(framework_sample Framework Utils)
TARGET_LINK_LIBRARIES(fsm_sample Utils)
TARGET_LINK_LIBRARIES(multimethods_sample Utils)
TARGET_LINK_LIBRARIES(network_sample Network Utils)
TARGET_LINK_LIBRARIES(visitor_sample Utils)
