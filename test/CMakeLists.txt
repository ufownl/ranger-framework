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

SET(test_Utils_Container_SOURCES
		Utils/Container/AssociateVectorTest.cpp
		Utils/Container/InstrusiveListTest.cpp
		Utils/Container/InstrusiveSlistTest.cpp
		Utils/Container/RoundRobinQueueTest.cpp
)

SET(test_Utils_Memory_SOURCES
		Utils/Memory/MemoryLeakDetectorTest.cpp
		Utils/Memory/STLAllocatorTest.cpp
)

SET(test_Utils_MPL_SOURCES
		Utils/MPL/BindTest.cpp
		Utils/MPL/FiniteStateMachineTest.cpp
		Utils/MPL/HierarchyGeneratorTest.cpp
)

SET(test_Utils_Multimethods_SOURCES
		Utils/Multimethods/MultimethodsTest.cpp
)

SET(test_Utils_Object_SOURCES
		Utils/Object/AbstractFactoryTest.cpp
		Utils/Object/FactoryTest.cpp
		Utils/Object/ObjectPoolTest.cpp
		Utils/Object/RefObjectTest.cpp
		Utils/Object/SingletonTest.cpp
		Utils/Object/SmartPointerTest.cpp
		Utils/Object/TypeInfoTest.cpp
		Utils/Object/VisitorTest.cpp
)

SET(test_Utils_System_SOURCES
		Utils/System/TimerTest.cpp
)

SET(test_Utils_Thread_SOURCES
		Utils/Thread/CoroutineTest.cpp
		Utils/Thread/MutexCallerTest.cpp
		Utils/Thread/ScopedLockTest.cpp
		Utils/Thread/ThreadLocalStorageTest.cpp
		Utils/Thread/ThreadPolicyTest.cpp
)

SET(test_Framework_SOURCES
		Framework/RfRunnableServiceTest.cpp
		Framework/RfServiceManagerTest.cpp
		Framework/RfServiceTest.cpp
)

SET(test_BehaviorTree_SOURCES
		BehaviorTree/BtBehaviorNodeTest.cpp
		BehaviorTree/BtCompositeNodeTest.cpp
		BehaviorTree/BtDecoratorNodeTest.cpp
)

INCLUDE_DIRECTORIES(
		${CMAKE_CURRENT_SOURCE_DIR}
		${RANGER_SOURCE_DIR}/Utils
		${RANGER_SOURCE_DIR}/Framework
		${RANGER_SOURCE_DIR}/BehaviorTree
		${RANGER_SOURCE_DIR}/Contribs/include
)

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

ADD_EXECUTABLE(test
		${test_Utils_Container_SOURCES}
		${test_Utils_Memory_SOURCES}
		${test_Utils_MPL_SOURCES}
		${test_Utils_Multimethods_SOURCES}
		${test_Utils_Object_SOURCES}
		${test_Utils_System_SOURCES}
		${test_Utils_Thread_SOURCES}
		${test_Framework_SOURCES}
		${test_BehaviorTree_SOURCES}
		main.cpp
)

ADD_DEPENDENCIES(test Utils Framework BehaviorTree)

LINK_DIRECTORIES(${RANGER_SOURCE_DIR}/Contribs/lib)

TARGET_LINK_LIBRARIES(test cppunit BehaviorTree Framework Utils)
