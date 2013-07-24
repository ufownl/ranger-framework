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

SET(Container_HEADERS
		Container/associate_vector.h
		Container/instrusive_list.h
		Container/instrusive_slist.h
		Container/round_robin_queue.h
)

IF(WIN32)
	SET(Memory_HEADERS
			Memory/Allocator.h
			Memory/MemoryLeakDetector.h
			Memory/STLAllocator.h
			Memory/TCMallocAllocator.h
	)

	SET(Memory_SOURCES
			Memory/Allocator.cpp
			Memory/MemoryLeakDetector.cpp
			Memory/TCMallocAllocator.cpp
	)
ELSE(WIN32)
	SET(Memory_HEADERS
			Memory/Allocator.h
			Memory/MemoryLeakDetector.h
			Memory/STLAllocator.h
	)

	SET(Memory_SOURCES
			Memory/Allocator.cpp
			Memory/MemoryLeakDetector.cpp
	)
ENDIF(WIN32)

SET(MPL_HEADERS
		MPL/bind.h
		MPL/dummy.h
		MPL/event_dispatcher.h
		MPL/finite_state_machine.h
		MPL/generate_dispatcher.h
		MPL/hierarchy_generator.h
)

SET(Multimethods_HEADERS
		Multimethods/BasicDispatcher.h
		Multimethods/DynamicDispatcher.h
		Multimethods/FastDispatcher.h
		Multimethods/StaticDispatcher.h
)

SET(Object_HEADERS
		Object/AbstractFactory.h
		Object/Factory.h
		Object/MemObject.h
		Object/ObjectPool.h
		Object/RefObject.h
		Object/Singleton.h
		Object/SmartPointer.h
		Object/TypeInfo.h
		Object/Visitor.h
)

SET(Object_SOURCES
		Object/TypeInfo.cpp
)

SET(Process_HEADERS
		Process/AtExit.h
)

SET(Process_SOURCES
		Process/AtExit.cpp
)

SET(System_HEADERS
		System/Timer.h
)

SET(System_SOURCES
		System/Timer.cpp
)

SET(Thread_HEADERS
		Thread/Coroutine.h
		Thread/Mutex.h
		Thread/MutexCaller.h
		Thread/ScopedLock.h
		Thread/ThreadLocalStorage.h
		Thread/ThreadPolicy.h
)

SET(Thread_SOURCES
		Thread/Coroutine.cpp
		Thread/Mutex.cpp
)

INCLUDE_DIRECTORIES(
		${CMAKE_CURRENT_SOURCE_DIR}
		${RANGER_SOURCE_DIR}/Contribs/include
)

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

SET(LIBRARY_OUTPUT_PATH ${RANGER_BINARY_DIR}/lib)

IF(WIN32)
	ADD_LIBRARY(Utils STATIC
			${Container_HEADERS}
			${Memory_HEADERS}
			${Memory_SOURCES}
			${MPL_HEADERS}
			${Multimethods_HEADERS}
			${Object_HEADERS}
			${Object_SOURCES}
			${Process_HEADERS}
			${Process_SOURCES}
			${System_HEADERS}
			${System_SOURCES}
			${Thread_HEADERS}
			${Thread_SOURCES}
	)
ELSE(WIN32)
	ADD_LIBRARY(Utils SHARED
			${Container_HEADERS}
			${Memory_HEADERS}
			${Memory_SOURCES}
			${MPL_HEADERS}
			${Multimethods_HEADERS}
			${Object_HEADERS}
			${Object_SOURCES}
			${Process_HEADERS}
			${Process_SOURCES}
			${System_HEADERS}
			${System_SOURCES}
			${Thread_HEADERS}
			${Thread_SOURCES}
	)
ENDIF(WIN32)

LINK_DIRECTORIES(${RANGER_SOURCE_DIR}/Contribs/lib)

IF(NOT WIN32)
	IF(APPLE)
		TARGET_LINK_LIBRARIES(Utils dl pthread)
	ELSE(APPLE)
		TARGET_LINK_LIBRARIES(Utils dl rt pthread)
	ENDIF(APPLE)
ENDIF(NOT WIN32)

INSTALL(TARGETS Utils DESTINATION lib)
INSTALL(FILES ${Container_HEADERS} DESTINATION include/Container)
INSTALL(FILES ${Memory_HEADERS} DESTINATION include/Memory)
INSTALL(FILES ${MPL_HEADERS} DESTINATION include/MPL)
INSTALL(FILES ${Multimethods_HEADERS} DESTINATION include/Multimethods)
INSTALL(FILES ${Object_HEADERS} DESTINATION include/Object)
INSTALL(FILES ${Process_HEADERS} DESTINATION include/Process)
INSTALL(FILES ${System_HEADERS} DESTINATION include/System)
INSTALL(FILES ${Thread_HEADERS} DESTINATION include/Thread)
