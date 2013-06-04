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
ldflags_debug = -L$(out_dir) -lUtils_debug -lluabind -llua
ldflags_release = -L$(out_dir) -lUtils -lluabind -llua

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

out_debug = $(out_dir)/libBehaviorTree_debug.so
out_release = $(out_dir)/libBehaviorTree.so

BtParams_debug_o = $(obj_dir_debug)/BtParams.o
BtNode_debug_o = $(obj_dir_debug)/BtNode.o
BtSelectorNode_debug_o = $(obj_dir_debug)/BtSelectorNode.o
BtSequenceNode_debug_o = $(obj_dir_debug)/BtSequenceNode.o
BtParallelSucceedOnAllNode_debug_o = $(obj_dir_debug)/BtParallelSucceedOnAllNode.o
BtParallelFailOnAllNode_debug_o = $(obj_dir_debug)/BtParallelFailOnAllNode.o
BtParallelHybridNode_debug_o = $(obj_dir_debug)/BtParallelHybridNode.o
BtDecoratorNotNode_debug_o = $(obj_dir_debug)/BtDecoratorNotNode.o
BtDecoratorTimerNode_debug_o = $(obj_dir_debug)/BtDecoratorTimerNode.o
BtDecoratorCounterNode_debug_o = $(obj_dir_debug)/BtDecoratorCounterNode.o
BtDecoratorForNode_debug_o = $(obj_dir_debug)/BtDecoratorForNode.o
BtDecoratorUntilNode_debug_o = $(obj_dir_debug)/BtDecoratorUntilNode.o
BtBehaviorNode_debug_o = $(obj_dir_debug)/BtBehaviorNode.o
BtConditionNode_debug_o = $(obj_dir_debug)/BtConditionNode.o
BtActionNode_debug_o = $(obj_dir_debug)/BtActionNode.o
BtXmlGenerator_debug_o = $(obj_dir_debug)/BtXmlGenerator.o

BtParams_release_o = $(obj_dir_release)/BtParams.o
BtNode_release_o = $(obj_dir_release)/BtNode.o
BtSelectorNode_release_o = $(obj_dir_release)/BtSelectorNode.o
BtSequenceNode_release_o = $(obj_dir_release)/BtSequenceNode.o
BtParallelSucceedOnAllNode_release_o = $(obj_dir_release)/BtParallelSucceedOnAllNode.o
BtParallelFailOnAllNode_release_o = $(obj_dir_release)/BtParallelFailOnAllNode.o
BtParallelHybridNode_release_o = $(obj_dir_release)/BtParallelHybridNode.o
BtDecoratorNotNode_release_o = $(obj_dir_release)/BtDecoratorNotNode.o
BtDecoratorTimerNode_release_o = $(obj_dir_release)/BtDecoratorTimerNode.o
BtDecoratorCounterNode_release_o = $(obj_dir_release)/BtDecoratorCounterNode.o
BtDecoratorForNode_release_o = $(obj_dir_release)/BtDecoratorForNode.o
BtDecoratorUntilNode_release_o = $(obj_dir_release)/BtDecoratorUntilNode.o
BtBehaviorNode_release_o = $(obj_dir_release)/BtBehaviorNode.o
BtConditionNode_release_o = $(obj_dir_release)/BtConditionNode.o
BtActionNode_release_o = $(obj_dir_release)/BtActionNode.o
BtXmlGenerator_release_o = $(obj_dir_release)/BtXmlGenerator.o

obj_debug = $(BtParams_debug_o) $(BtNode_debug_o) $(BtSelectorNode_debug_o) $(BtSequenceNode_debug_o) $(BtParallelSucceedOnAllNode_debug_o) $(BtParallelFailOnAllNode_debug_o) $(BtParallelHybridNode_debug_o) $(BtDecoratorNotNode_debug_o) $(BtDecoratorTimerNode_debug_o) $(BtDecoratorCounterNode_debug_o) $(BtDecoratorForNode_debug_o) $(BtDecoratorUntilNode_debug_o) $(BtBehaviorNode_debug_o) $(BtConditionNode_debug_o) $(BtActionNode_debug_o) $(BtXmlGenerator_debug_o)
obj_release = $(BtParams_release_o) $(BtNode_release_o) $(BtSelectorNode_release_o) $(BtSequenceNode_release_o) $(BtParallelSucceedOnAllNode_release_o) $(BtParallelFailOnAllNode_release_o) $(BtParallelHybridNode_release_o) $(BtDecoratorNotNode_release_o) $(BtDecoratorTimerNode_release_o) $(BtDecoratorCounterNode_release_o) $(BtDecoratorForNode_release_o) $(BtDecoratorUntilNode_release_o) $(BtBehaviorNode_release_o) $(BtConditionNode_release_o) $(BtActionNode_release_o) $(BtXmlGenerator_release_o)

BtParams_src = BtParams.cpp
BtNode_src = BtNode.cpp
BtSelectorNode_src = BtSelectorNode.cpp
BtSequenceNode_src = BtSequenceNode.cpp
BtParallelSucceedOnAllNode_src = BtParallelSucceedOnAllNode.cpp
BtParallelFailOnAllNode_src = BtParallelFailOnAllNode.cpp
BtParallelHybridNode_src = BtParallelHybridNode.cpp
BtDecoratorNotNode_src = BtDecoratorNotNode.cpp
BtDecoratorTimerNode_src = BtDecoratorTimerNode.cpp
BtDecoratorCounterNode_src = BtDecoratorCounterNode.cpp
BtDecoratorForNode_src = BtDecoratorForNode.cpp
BtDecoratorUntilNode_src = BtDecoratorUntilNode.cpp
BtBehaviorNode_src = BtBehaviorNode.cpp
BtConditionNode_src = BtConditionNode.cpp
BtActionNode_src = BtActionNode.cpp
BtXmlGenerator_src = BtXmlGenerator.cpp

all: $(out_debug) $(out_release)

$(out_debug): $(obj_debug)
	$(ld_debug)

$(out_release): $(obj_release)
	$(ld_release)

$(BtParams_debug_o): $(BtParams_src)
	$(cxx_debug)

$(BtNode_debug_o): $(BtNode_src)
	$(cxx_debug)

$(BtSelectorNode_debug_o): $(BtSelectorNode_src)
	$(cxx_debug)

$(BtSequenceNode_debug_o): $(BtSequenceNode_src)
	$(cxx_debug)

$(BtParallelSucceedOnAllNode_debug_o): $(BtParallelSucceedOnAllNode_src)
	$(cxx_debug)

$(BtParallelFailOnAllNode_debug_o): $(BtParallelFailOnAllNode_src)
	$(cxx_debug)

$(BtParallelHybridNode_debug_o): $(BtParallelHybridNode_src)
	$(cxx_debug)

$(BtDecoratorNotNode_debug_o): $(BtDecoratorNotNode_src)
	$(cxx_debug)

$(BtDecoratorTimerNode_debug_o): $(BtDecoratorTimerNode_src)
	$(cxx_debug)

$(BtDecoratorCounterNode_debug_o): $(BtDecoratorCounterNode_src)
	$(cxx_debug)

$(BtDecoratorForNode_debug_o): $(BtDecoratorForNode_src)
	$(cxx_debug)

$(BtDecoratorUntilNode_debug_o): $(BtDecoratorUntilNode_src)
	$(cxx_debug)

$(BtBehaviorNode_debug_o): $(BtBehaviorNode_src)
	$(cxx_debug)

$(BtConditionNode_debug_o): $(BtConditionNode_src)
	$(cxx_debug)

$(BtActionNode_debug_o): $(BtActionNode_src)
	$(cxx_debug)

$(BtXmlGenerator_debug_o): $(BtXmlGenerator_src)
	$(cxx_debug)

$(BtParams_release_o): $(BtParams_src)
	$(cxx_release)

$(BtNode_release_o): $(BtNode_src)
	$(cxx_release)

$(BtSelectorNode_release_o): $(BtSelectorNode_src)
	$(cxx_release)

$(BtSequenceNode_release_o): $(BtSequenceNode_src)
	$(cxx_release)

$(BtParallelSucceedOnAllNode_release_o): $(BtParallelSucceedOnAllNode_src)
	$(cxx_release)

$(BtParallelFailOnAllNode_release_o): $(BtParallelFailOnAllNode_src)
	$(cxx_release)

$(BtParallelHybridNode_release_o): $(BtParallelHybridNode_src)
	$(cxx_release)

$(BtDecoratorNotNode_release_o): $(BtDecoratorNotNode_src)
	$(cxx_release)

$(BtDecoratorTimerNode_release_o): $(BtDecoratorTimerNode_src)
	$(cxx_release)

$(BtDecoratorCounterNode_release_o): $(BtDecoratorCounterNode_src)
	$(cxx_release)

$(BtDecoratorForNode_release_o): $(BtDecoratorForNode_src)
	$(cxx_release)

$(BtDecoratorUntilNode_release_o): $(BtDecoratorUntilNode_src)
	$(cxx_release)

$(BtBehaviorNode_release_o): $(BtBehaviorNode_src)
	$(cxx_release)

$(BtConditionNode_release_o): $(BtConditionNode_src)
	$(cxx_release)

$(BtActionNode_release_o): $(BtActionNode_src)
	$(cxx_release)

$(BtXmlGenerator_release_o): $(BtXmlGenerator_src)
	$(cxx_release)

clean:
	rm -f $(out_debug)
	rm -f $(out_release)
	rm -f $(obj_debug)
	rm -f $(obj_release)

.PHONY: all clean
