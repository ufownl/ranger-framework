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

SET(BehaviorTree_HEADERS
		BtActionNode.h
		BtBehaviorNode.h
		BtConditionNode.h
		BtDecoratorCounterNode.h
		BtDecoratorForNode.h
		BtDecoratorNotNode.h
		BtDecoratorTimerNode.h
		BtDecoratorUntilNode.h
		BtNode.h
		BtParallelFailOnAllNode.h
		BtParallelHybridNode.h
		BtParallelSucceedOnAllNode.h
		BtParams.h
		BtSelectorNode.h
		BtSequenceNode.h
		BtXmlGenerator.h
)

SET(BehaviorTree_SOURCES
		BtActionNode.cpp
		BtBehaviorNode.cpp
		BtConditionNode.cpp
		BtDecoratorCounterNode.cpp
		BtDecoratorForNode.cpp
		BtDecoratorNotNode.cpp
		BtDecoratorTimerNode.cpp
		BtDecoratorUntilNode.cpp
		BtNode.cpp
		BtParallelFailOnAllNode.cpp
		BtParallelHybridNode.cpp
		BtParallelSucceedOnAllNode.cpp
		BtParams.cpp
		BtSelectorNode.cpp
		BtSequenceNode.cpp
		BtXmlGenerator.cpp
)

INCLUDE_DIRECTORIES(
		${CMAKE_CURRENT_SOURCE_DIR}
		${RANGER_SOURCE_DIR}/Utils
		${RANGER_SOURCE_DIR}/Contribs/include
)

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

SET(LIBRARY_OUTPUT_PATH ${RANGER_BINARY_DIR}/lib)

ADD_LIBRARY(BehaviorTree SHARED
		${BehaviorTree_HEADERS}
		${BehaviorTree_SOURCES}
)

ADD_DEPENDENCIES(BehaviorTree Utils)

LINK_DIRECTORIES(${RANGER_SOURCE_DIR}/Contribs/lib)

TARGET_LINK_LIBRARIES(BehaviorTree Utils luabind lua)

INSTALL(TARGETS BehaviorTree DESTINATION lib)
INSTALL(FILES ${BehaviorTree_HEADERS} DESTINATION include)
