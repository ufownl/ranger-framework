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

Utils_dir = ./Utils
Framework_dir = ./Framework
BehTree_dir = ./BehaviorTree

cflags_debug = -g -fPIC -Wall -D_DEBUG -I$(Utils_dir) -I$(Framework_dir) -I$(BehTree_dir)
cflags_release = -O2 -fPIC -Wall -DNDEBUG -I$(Utils_dir) -I$(Framework_dir) -I$(BehTree_dir)
ldflags_debug = -lluabind -llua -ldl -lpthread
ldflags_release = -lluabind -llua -ldl -lpthread

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

out_dir = ./lib

out_debug = $(out_dir)/libRangerFramework_debug.so
out_release = $(out_dir)/libRangerFramework.so

obj_dir = ./obj
obj_dir_debug = $(obj_dir)/debug
obj_dir_release = $(obj_dir)/release

Allocator_debug_o = $(obj_dir_debug)/Allocator.o
MemoryLeakDetector_debug_o = $(obj_dir_debug)/MemoryLeakDetector.o
Mutex_debug_o = $(obj_dir_debug)/Mutex.o
TypeInfo_debug_o = $(obj_dir_debug)/TypeInfo.o
Coroutine_debug_o = $(obj_dir_debug)/Coroutine.o
AtExit_debug_o = $(obj_dir_debug)/AtExit.o
RfAction_debug_o = $(obj_dir_debug)/RfAction.o
RfActionHandler_debug_o = $(obj_dir_debug)/RfActionHandler.o
RfRequestService_debug_o = $(obj_dir_debug)/RfRequestService.o
RfRunnableService_debug_o = $(obj_dir_debug)/RfRunnableService.o
RfService_debug_o = $(obj_dir_debug)/RfService.o
RfServiceManager_debug_o = $(obj_dir_debug)/RfServiceManager.o
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

Allocator_release_o = $(obj_dir_release)/Allocator.o
MemoryLeakDetector_release_o = $(obj_dir_release)/MemoryLeakDetector.o
Mutex_release_o = $(obj_dir_release)/Mutex.o
TypeInfo_release_o = $(obj_dir_release)/TypeInfo.o
Coroutine_release_o = $(obj_dir_release)/Coroutine.o
AtExit_release_o = $(obj_dir_release)/AtExit.o
RfAction_release_o = $(obj_dir_release)/RfAction.o
RfActionHandler_release_o = $(obj_dir_release)/RfActionHandler.o
RfRequestService_release_o = $(obj_dir_release)/RfRequestService.o
RfRunnableService_release_o = $(obj_dir_release)/RfRunnableService.o
RfService_release_o = $(obj_dir_release)/RfService.o
RfServiceManager_release_o = $(obj_dir_release)/RfServiceManager.o
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

obj_debug = $(Allocator_debug_o) $(MemoryLeakDetector_debug_o) $(Mutex_debug_o) $(TypeInfo_debug_o) $(Coroutine_debug_o) $(AtExit_debug_o) $(RfAction_debug_o) $(RfActionHandler_debug_o) $(RfRequestService_debug_o) $(RfRunnableService_debug_o) $(RfService_debug_o) $(RfServiceManager_debug_o) $(BtParams_debug_o) $(BtNode_debug_o) $(BtSelectorNode_debug_o) $(BtSequenceNode_debug_o) $(BtParallelSucceedOnAllNode_debug_o) $(BtParallelFailOnAllNode_debug_o) $(BtParallelHybridNode_debug_o) $(BtDecoratorNotNode_debug_o) $(BtDecoratorTimerNode_debug_o) $(BtDecoratorCounterNode_debug_o) $(BtDecoratorForNode_debug_o) $(BtDecoratorUntilNode_debug_o) $(BtBehaviorNode_debug_o) $(BtConditionNode_debug_o) $(BtActionNode_debug_o) $(BtXmlGenerator_debug_o)
obj_release = $(Allocator_release_o) $(MemoryLeakDetector_release_o) $(Mutex_release_o) $(TypeInfo_release_o) $(Coroutine_release_o) $(AtExit_release_o) $(RfAction_release_o) $(RfActionHandler_release_o) $(RfRequestService_release_o) $(RfRunnableService_release_o) $(RfService_release_o) $(RfServiceManager_release_o) $(BtParams_release_o) $(BtNode_release_o) $(BtSelectorNode_release_o) $(BtSequenceNode_release_o) $(BtParallelSucceedOnAllNode_release_o) $(BtParallelFailOnAllNode_release_o) $(BtParallelHybridNode_release_o) $(BtDecoratorNotNode_release_o) $(BtDecoratorTimerNode_release_o) $(BtDecoratorCounterNode_release_o) $(BtDecoratorForNode_release_o) $(BtDecoratorUntilNode_release_o) $(BtBehaviorNode_release_o) $(BtConditionNode_release_o) $(BtActionNode_release_o) $(BtXmlGenerator_release_o)

Allocator_src = $(Utils_dir)/Memory/Allocator.cpp
MemoryLeakDetector_src = $(Utils_dir)/Memory/MemoryLeakDetector.cpp
Mutex_src = $(Utils_dir)/Thread/Mutex.cpp
TypeInfo_src = $(Utils_dir)/Object/TypeInfo.cpp
Coroutine_src = $(Utils_dir)/Thread/Coroutine.cpp
AtExit_src = $(Utils_dir)/Process/AtExit.cpp
RfAction_src = $(Framework_dir)/RfAction.cpp
RfActionHandler_src = $(Framework_dir)/RfActionHandler.cpp
RfRequestService_src = $(Framework_dir)/RfRequestService.cpp
RfRunnableService_src = $(Framework_dir)/RfRunnableService.cpp
RfService_src = $(Framework_dir)/RfService.cpp
RfServiceManager_src = $(Framework_dir)/RfServiceManager.cpp
BtParams_src = $(BehTree_dir)/BtParams.cpp
BtNode_src = $(BehTree_dir)/BtNode.cpp
BtSelectorNode_src = $(BehTree_dir)/BtSelectorNode.cpp
BtSequenceNode_src = $(BehTree_dir)/BtSequenceNode.cpp
BtParallelSucceedOnAllNode_src = $(BehTree_dir)/BtParallelSucceedOnAllNode.cpp
BtParallelFailOnAllNode_src = $(BehTree_dir)/BtParallelFailOnAllNode.cpp
BtParallelHybridNode_src = $(BehTree_dir)/BtParallelHybridNode.cpp
BtDecoratorNotNode_src = $(BehTree_dir)/BtDecoratorNotNode.cpp
BtDecoratorTimerNode_src = $(BehTree_dir)/BtDecoratorTimerNode.cpp
BtDecoratorCounterNode_src = $(BehTree_dir)/BtDecoratorCounterNode.cpp
BtDecoratorForNode_src = $(BehTree_dir)/BtDecoratorForNode.cpp
BtDecoratorUntilNode_src = $(BehTree_dir)/BtDecoratorUntilNode.cpp
BtBehaviorNode_src = $(BehTree_dir)/BtBehaviorNode.cpp
BtConditionNode_src = $(BehTree_dir)/BtConditionNode.cpp
BtActionNode_src = $(BehTree_dir)/BtActionNode.cpp
BtXmlGenerator_src = $(BehTree_dir)/BtXmlGenerator.cpp

all: create_dir $(out_debug) $(out_release)
	make -C Samples
	make -C test

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

create_dir:
	mkdir -p $(obj_dir_debug)
	mkdir -p $(obj_dir_release)
	mkdir -p $(out_dir)

clean:
	make -C test clean
	make -C Samples clean
	rm -f $(out_debug)
	rm -f $(out_release)
	rm -f $(obj_debug)
	rm -f $(obj_release)
	-rmdir $(out_dir)
	-rmdir $(obj_dir_debug)
	-rmdir $(obj_dir_release)
	-rmdir $(obj_dir)

.PHONY: all create_dir clean
