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

cxx = g++
ld = g++

Utils_dir = ../Utils
Framework_dir = ../Framework
BehTree_dir = ../BehaviorTree

cflags = -g -Wall -D_DEBUG -I$(Utils_dir) -I$(Framework_dir) -I$(BehTree_dir)
ldflags = -L../lib -lcppunit -lRangerFramework_debug -lluabind -llua -ldl -lpthread

define cxx_run
$(cxx) -c $(cflags) $^ -o $@
endef

define ld_run
$(ld) $^ $(ldflags) -o $@
endef

all: test

test: main.o ScopedLockTest.o MutexCallerTest.o ThreadPolicyTest.o CoroutineTest.o ThreadLocalStorageTest.o MemoryLeakDetectorTest.o STLAllocatorTest.o AssociateVectorTest.o InstrusiveListTest.o
	$(ld_run)

main.o: main.cpp
	$(cxx_run)

ScopedLockTest.o: Utils/Thread/ScopedLockTest.cpp
	$(cxx_run)

MutexCallerTest.o: Utils/Thread/MutexCallerTest.cpp
	$(cxx_run)

ThreadPolicyTest.o: Utils/Thread/ThreadPolicyTest.cpp
	$(cxx_run)

CoroutineTest.o: Utils/Thread/CoroutineTest.cpp
	$(cxx_run)

ThreadLocalStorageTest.o: Utils/Thread/ThreadLocalStorageTest.cpp
	$(cxx_run)

MemoryLeakDetectorTest.o: Utils/Memory/MemoryLeakDetectorTest.cpp
	$(cxx_run)

STLAllocatorTest.o: Utils/Memory/STLAllocatorTest.cpp
	$(cxx_run)

AssociateVectorTest.o: Utils/Container/AssociateVectorTest.cpp
	$(cxx_run)

InstrusiveListTest.o: Utils/Container/InstrusiveListTest.cpp
	$(cxx_run)

clean:
	rm -f test *.o

.PHONY: all clean
