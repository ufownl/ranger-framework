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

plat = linux

cxx = g++
ld = g++

out_dir = ../lib
obj_dir = ../obj
obj_dir_debug = $(obj_dir)/debug
obj_dir_release = $(obj_dir)/release

cflags_debug = -g -fPIC -Wall -D_DEBUG -I.
cflags_release = -O2 -fPIC -Wall -DNDEBUG -I.
ifeq ($(plat), linux)
ldflags_debug = -ldl -lrt -lpthread
ldflags_release = -ldl -lrt -lpthread
else
ldflags_debug = -ldl -lpthread
ldflags_release = -ldl -lpthread
endif

define cxx_debug
$(cxx) -c $(cflags_debug) $^ -o $@
endef

define cxx_release
$(cxx) -c $(cflags_release) $^ -o $@
endef

define ld_debug
$(ld) -shared $^ $(ldflags_debug) -o $@
endef

define ld_release
$(ld) -shared $^ $(ldflags_release) -o $@
endef

out_debug = $(out_dir)/libUtils_debug.so
out_release = $(out_dir)/libUtils.so

Allocator_debug_o = $(obj_dir_debug)/Allocator.o
MemoryLeakDetector_debug_o = $(obj_dir_debug)/MemoryLeakDetector.o
Mutex_debug_o = $(obj_dir_debug)/Mutex.o
TypeInfo_debug_o = $(obj_dir_debug)/TypeInfo.o
Coroutine_debug_o = $(obj_dir_debug)/Coroutine.o
AtExit_debug_o = $(obj_dir_debug)/AtExit.o
Timer_debug_o = $(obj_dir_debug)/Timer.o

Allocator_release_o = $(obj_dir_release)/Allocator.o
MemoryLeakDetector_release_o = $(obj_dir_release)/MemoryLeakDetector.o
Mutex_release_o = $(obj_dir_release)/Mutex.o
TypeInfo_release_o = $(obj_dir_release)/TypeInfo.o
Coroutine_release_o = $(obj_dir_release)/Coroutine.o
AtExit_release_o = $(obj_dir_release)/AtExit.o
Timer_release_o = $(obj_dir_release)/Timer.o

obj_debug = $(Allocator_debug_o) $(MemoryLeakDetector_debug_o) $(Mutex_debug_o) $(TypeInfo_debug_o) $(Coroutine_debug_o) $(AtExit_debug_o) $(Timer_debug_o)
obj_release = $(Allocator_release_o) $(MemoryLeakDetector_release_o) $(Mutex_release_o) $(TypeInfo_release_o) $(Coroutine_release_o) $(AtExit_release_o) $(Timer_release_o)

Allocator_src = Memory/Allocator.cpp
MemoryLeakDetector_src = Memory/MemoryLeakDetector.cpp
Mutex_src = Thread/Mutex.cpp
TypeInfo_src = Object/TypeInfo.cpp
Coroutine_src = Thread/Coroutine.cpp
AtExit_src = Process/AtExit.cpp
Timer_src = System/Timer.cpp

all: $(out_debug) $(out_release)

$(out_debug): $(obj_debug)
	$(ld_debug)

$(out_release): $(obj_release)
	$(ld_release)

$(Allocator_debug_o): $(Allocator_src)
	$(cxx_debug)

$(MemoryLeakDetector_debug_o): $(MemoryLeakDetector_src)
	$(cxx_debug)

$(Mutex_debug_o): $(Mutex_src)
	$(cxx_debug)

$(TypeInfo_debug_o): $(TypeInfo_src)
	$(cxx_debug)

$(Coroutine_debug_o): $(Coroutine_src)
	$(cxx_debug)

$(AtExit_debug_o): $(AtExit_src)
	$(cxx_debug)

$(Timer_debug_o): $(Timer_src)
	$(cxx_debug)

$(Allocator_release_o): $(Allocator_src)
	$(cxx_release)

$(MemoryLeakDetector_release_o): $(MemoryLeakDetector_src)
	$(cxx_release)

$(Mutex_release_o): $(Mutex_src)
	$(cxx_release)

$(TypeInfo_release_o): $(TypeInfo_src)
	$(cxx_release)

$(Coroutine_release_o): $(Coroutine_src)
	$(cxx_release)

$(AtExit_release_o): $(AtExit_src)
	$(cxx_release)

$(Timer_release_o): $(Timer_src)
	$(cxx_release)

clean:
	rm -f $(out_debug)
	rm -f $(out_release)
	rm -f $(obj_debug)
	rm -f $(obj_release)

.PHONY: all clean
