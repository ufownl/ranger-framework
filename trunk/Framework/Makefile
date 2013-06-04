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
ldflags_debug =
ldflags_release =

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

out_debug = $(out_dir)/libFramework_debug.so
out_release = $(out_dir)/libFramework.so

RfAction_debug_o = $(obj_dir_debug)/RfAction.o
RfActionHandler_debug_o = $(obj_dir_debug)/RfActionHandler.o
RfRequestService_debug_o = $(obj_dir_debug)/RfRequestService.o
RfRunnableService_debug_o = $(obj_dir_debug)/RfRunnableService.o
RfService_debug_o = $(obj_dir_debug)/RfService.o
RfServiceManager_debug_o = $(obj_dir_debug)/RfServiceManager.o

RfAction_release_o = $(obj_dir_release)/RfAction.o
RfActionHandler_release_o = $(obj_dir_release)/RfActionHandler.o
RfRequestService_release_o = $(obj_dir_release)/RfRequestService.o
RfRunnableService_release_o = $(obj_dir_release)/RfRunnableService.o
RfService_release_o = $(obj_dir_release)/RfService.o
RfServiceManager_release_o = $(obj_dir_release)/RfServiceManager.o

obj_debug = $(RfAction_debug_o) $(RfActionHandler_debug_o) $(RfRequestService_debug_o) $(RfRunnableService_debug_o) $(RfService_debug_o) $(RfServiceManager_debug_o)
obj_release = $(RfAction_release_o) $(RfActionHandler_release_o) $(RfRequestService_release_o) $(RfRunnableService_release_o) $(RfService_release_o) $(RfServiceManager_release_o)

RfAction_src = RfAction.cpp
RfActionHandler_src = RfActionHandler.cpp
RfRequestService_src = RfRequestService.cpp
RfRunnableService_src = RfRunnableService.cpp
RfService_src = RfService.cpp
RfServiceManager_src = RfServiceManager.cpp

all: $(out_debug) $(out_release)

$(out_debug): $(obj_debug)
	$(ld_debug)

$(out_release): $(obj_release)
	$(ld_release)

$(RfAction_debug_o): $(RfAction_src)
	$(cxx_debug)
			
$(RfActionHandler_debug_o): $(RfActionHandler_src)
	$(cxx_debug)

$(RfRequestService_debug_o): $(RfRequestService_src)
	$(cxx_debug)

$(RfRunnableService_debug_o): $(RfRunnableService_src)
	$(cxx_debug)

$(RfService_debug_o): $(RfService_src)
	$(cxx_debug)

$(RfServiceManager_debug_o): $(RfServiceManager_src)
	$(cxx_debug)

$(RfAction_release_o): $(RfAction_src)
	$(cxx_release)
			
$(RfActionHandler_release_o): $(RfActionHandler_src)
	$(cxx_release)

$(RfRequestService_release_o): $(RfRequestService_src)
	$(cxx_release)

$(RfRunnableService_release_o): $(RfRunnableService_src)
	$(cxx_release)

$(RfService_release_o): $(RfService_src)
	$(cxx_release)

$(RfServiceManager_release_o): $(RfServiceManager_src)
	$(cxx_release)

clean:
	rm -f $(out_debug)
	rm -f $(out_release)
	rm -f $(obj_debug)
	rm -f $(obj_release)

.PHONY: all clean
