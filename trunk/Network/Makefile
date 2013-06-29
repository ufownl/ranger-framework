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
out_dir = ../lib
obj_dir = ../obj
obj_dir_debug = $(obj_dir)/debug
obj_dir_release = $(obj_dir)/release

cflags_debug = -g -fPIC -Wall -D_DEBUG -I. -I$(Utils_dir)
cflags_release = -O2 -fPIC -Wall -DNDEBUG -I. -I$(Utils_dir)
ldflags_debug = -L$(out_dir) -lUtils_debug -levent_core -levent_pthreads
ldflags_release = -L$(out_dir) -lUtils -levent_core -levent_pthreads

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

out_debug = $(out_dir)/libNetwork_debug.so
out_release = $(out_dir)/libNetwork.so

NwInitializer_debug_o = $(obj_dir_debug)/NwInitializer.o
NwEventDispatcher_debug_o = $(obj_dir_debug)/NwEventDispatcher.o
NwBufferBase_debug_o = $(obj_dir_debug)/NwBufferBase.o
NwBuffer_debug_o = $(obj_dir_debug)/NwBuffer.o
NwListener_debug_o = $(obj_dir_debug)/NwListener.o
NwMessageFilter_debug_o = $(obj_dir_debug)/NwMessageFilter.o
NwEventHandler_debug_o = $(obj_dir_debug)/NwEventHandler.o
NwConnection_debug_o = $(obj_dir_debug)/NwConnection.o
NwNetService_debug_o = $(obj_dir_debug)/NwNetService.o

NwInitializer_release_o = $(obj_dir_release)/NwInitializer.o
NwEventDispatcher_release_o = $(obj_dir_release)/NwEventDispatcher.o
NwBufferBase_release_o = $(obj_dir_release)/NwBufferBase.o
NwBuffer_release_o = $(obj_dir_release)/NwBuffer.o
NwListener_release_o = $(obj_dir_release)/NwListener.o
NwMessageFilter_release_o = $(obj_dir_release)/NwMessageFilter.o
NwEventHandler_release_o = $(obj_dir_release)/NwEventHandler.o
NwConnection_release_o = $(obj_dir_release)/NwConnection.o
NwNetService_release_o = $(obj_dir_release)/NwNetService.o

NwInitializer_src = NwInitializer.cpp
NwEventDispatcher_src = NwEventDispatcher.cpp
NwBufferBase_src = NwBufferBase.cpp
NwBuffer_src = NwBuffer.cpp
NwListener_src = NwListener.cpp
NwMessageFilter_src = NwMessageFilter.cpp
NwEventHandler_src = NwEventHandler.cpp
NwConnection_src = NwConnection.cpp
NwNetService_src = NwNetService.cpp

obj_debug = $(NwInitializer_debug_o) $(NwEventDispatcher_debug_o) $(NwBufferBase_debug_o) $(NwBuffer_debug_o) $(NwListener_debug_o) $(NwMessageFilter_debug_o) $(NwEventHandler_debug_o) $(NwConnection_debug_o) $(NwNetService_debug_o)
obj_release = $(NwInitializer_release_o) $(NwEventDispatcher_release_o) $(NwBufferBase_release_o) $(NwBuffer_release_o) $(NwListener_release_o) $(NwMessageFilter_release_o) $(NwEventHandler_release_o) $(NwConnection_release_o) $(NwNetService_release_o)

all: $(out_debug) $(out_release)

$(out_debug): $(obj_debug)
	$(ld_debug)

$(out_release): $(obj_release)
	$(ld_release)

$(NwInitializer_debug_o): $(NwInitializer_src)
	$(cxx_debug)

$(NwEventDispatcher_debug_o): $(NwEventDispatcher_src)
	$(cxx_debug)

$(NwBufferBase_debug_o): $(NwBufferBase_src)
	$(cxx_debug)

$(NwBuffer_debug_o): $(NwBuffer_src)
	$(cxx_debug)

$(NwListener_debug_o): $(NwListener_src)
	$(cxx_debug)

$(NwMessageFilter_debug_o): $(NwMessageFilter_src)
	$(cxx_debug)

$(NwEventHandler_debug_o): $(NwEventHandler_src)
	$(cxx_debug)

$(NwConnection_debug_o): $(NwConnection_src)
	$(cxx_debug)

$(NwNetService_debug_o): $(NwNetService_src)
	$(cxx_debug)

$(NwInitializer_release_o): $(NwInitializer_src)
	$(cxx_release)

$(NwEventDispatcher_release_o): $(NwEventDispatcher_src)
	$(cxx_release)

$(NwBufferBase_release_o): $(NwBufferBase_src)
	$(cxx_release)

$(NwBuffer_release_o): $(NwBuffer_src)
	$(cxx_release)

$(NwListener_release_o): $(NwListener_src)
	$(cxx_release)

$(NwMessageFilter_release_o): $(NwMessageFilter_src)
	$(cxx_release)

$(NwEventHandler_release_o): $(NwEventHandler_src)
	$(cxx_release)

$(NwConnection_release_o): $(NwConnection_src)
	$(cxx_release)

$(NwNetService_release_o): $(NwNetService_src)
	$(cxx_release)

clean:
	rm -f $(out_debug)
	rm -f $(out_release)
	rm -f $(obj_debug)
	rm -f $(obj_release)

.PHONY: all clean
