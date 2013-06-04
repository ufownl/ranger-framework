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

cflags_debug = -g -Wall -D_DEBUG -I$(Utils_dir) -I$(Framework_dir) -I$(BehTree_dir)
cflags_release = -O2 -Wall -DNDEBUG -I$(Utils_dir) -I$(Framework_dir) -I$(BehTree_dir)
ldflags_debug = -L../lib -lBehaviorTree_debug -lFramework_debug -lUtils_debug -lluabind -llua -ldl -lpthread
ldflags_release = -L../lib -lBehaviorTree -lFramework -lUtils -lluabind -llua -ldl -lpthread

define cxx_debug
$(cxx) -c $(cflags_debug) $^ -o $@
endef

define cxx_release
$(cxx) -c $(cflags_release) $^ -o $@
endef

define ld_debug
$(ld) $^ $(ldflags_debug) -o $@
endef

define ld_release
$(ld) $^ $(ldflags_release) -o $@
endef

out_debug = multimethods_sample_debug factory_sample_debug visitor_sample_debug fsm_sample_debug coroutine_sample_debug framework_sample_debug bt_sample_debug
out_release = multimethods_sample factory_sample visitor_sample fsm_sample coroutine_sample framework_sample bt_sample

all: $(out_debug) $(out_release)

multimethods_sample_debug: multimethods_sample_debug.o
	$(ld_debug)

factory_sample_debug: factory_sample_debug.o
	$(ld_debug)

visitor_sample_debug: visitor_sample_debug.o
	$(ld_debug)

fsm_sample_debug: fsm_sample_debug.o
	$(ld_debug)

coroutine_sample_debug: coroutine_sample_debug.o
	$(ld_debug)

framework_sample_debug: framework_sample_debug.o
	$(ld_debug)

bt_sample_debug: bt_sample_debug.o
	$(ld_debug)

multimethods_sample_debug.o: multimethods_sample.cpp
	$(cxx_debug)

factory_sample_debug.o: factory_sample.cpp
	$(cxx_debug)

visitor_sample_debug.o: visitor_sample.cpp
	$(cxx_debug)

fsm_sample_debug.o: fsm_sample.cpp
	$(cxx_debug)

coroutine_sample_debug.o: coroutine_sample.cpp
	$(cxx_debug)

framework_sample_debug.o: framework_sample.cpp
	$(cxx_debug)

bt_sample_debug.o: bt_sample.cpp
	$(cxx_debug)

multimethods_sample: multimethods_sample.o
	$(ld_release)

factory_sample: factory_sample.o
	$(ld_release)

visitor_sample: visitor_sample.o
	$(ld_release)

fsm_sample: fsm_sample.o
	$(ld_release)

coroutine_sample: coroutine_sample.o
	$(ld_release)

framework_sample: framework_sample.o
	$(ld_release)

bt_sample: bt_sample.o
	$(ld_release)

multimethods_sample.o: multimethods_sample.cpp
	$(cxx_release)

factory_sample.o: factory_sample.cpp
	$(cxx_release)

visitor_sample.o: visitor_sample.cpp
	$(cxx_release)

fsm_sample.o: fsm_sample.cpp
	$(cxx_release)

coroutine_sample.o: coroutine_sample.cpp
	$(cxx_release)

framework_sample.o: framework_sample.cpp
	$(cxx_release)

bt_sample.o: bt_sample.cpp
	$(cxx_release)

clean:
	rm -f $(out_debug)
	rm -f $(out_release)
	rm -f *.o

.PHONY: all clean
