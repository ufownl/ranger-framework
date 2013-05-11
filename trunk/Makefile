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

CXX = g++
LD = g++
BEHTREE = ./BehaviorTree
FRAMEWORK = ./Framework
UTILS = ./Utils
SAMPLES = ./Samples
CFLAGS = -g -Wall -D_DEBUG -I$(UTILS) -I$(FRAMEWORK) -I$(BEHTREE)
LDFLAGS = -lluabind -llua -ldl -lpthread
OBJS = BtParams.o BtNode.o BtSelectorNode.o BtSequenceNode.o BtParallelSucceedOnAllNode.o BtParallelFailOnAllNode.o BtParallelHybridNode.o BtDecoratorNotNode.o BtDecoratorTimerNode.o BtDecoratorCounterNode.o BtDecoratorForNode.o BtDecoratorUntilNode.o BtBehaviorNode.o BtConditionNode.o BtActionNode.o BtXmlGenerator.o RfAction.o RfActionHandler.o RfRequestService.o RfRunnableService.o RfService.o RfServiceManager.o Allocator.o MemoryLeakDetector.o Mutex.o TypeInfo.o Coroutine.o
OUTPUT = multimethods_sample factory_sample visitor_sample fsm_sample coroutine_sample framework_sample bt_sample

all: $(OUTPUT)

multimethods_sample: multimethods_sample.o $(OBJS)
	$(LD) $(OBJS) multimethods_sample.o $(LDFLAGS) -o $@

factory_sample: factory_sample.o $(OBJS)
	$(LD) $(OBJS) factory_sample.o $(LDFLAGS) -o $@

visitor_sample: visitor_sample.o $(OBJS)
	$(LD) $(OBJS) visitor_sample.o $(LDFLAGS) -o $@

fsm_sample: fsm_sample.o $(OBJS)
	$(LD) $(OBJS) fsm_sample.o $(LDFLAGS) -o $@

coroutine_sample: coroutine_sample.o $(OBJS)
	$(LD) $(OBJS) coroutine_sample.o $(LDFLAGS) -o $@

framework_sample: framework_sample.o $(OBJS)
	$(LD) $(OBJS) framework_sample.o $(LDFLAGS) -o $@

bt_sample: bt_sample.o $(OBJS)
	$(LD) $(OBJS) bt_sample.o $(LDFLAGS) -o $@

multimethods_sample.o: $(SAMPLES)/multimethods_sample.cpp
	$(CXX) -c $(CFLAGS) $(SAMPLES)/multimethods_sample.cpp

factory_sample.o: $(SAMPLES)/factory_sample.cpp
	$(CXX) -c $(CFLAGS) $(SAMPLES)/factory_sample.cpp

visitor_sample.o: $(SAMPLES)/visitor_sample.cpp
	$(CXX) -c $(CFLAGS) $(SAMPLES)/visitor_sample.cpp

fsm_sample.o: $(SAMPLES)/fsm_sample.cpp
	$(CXX) -c $(CFLAGS) $(SAMPLES)/fsm_sample.cpp

coroutine_sample.o: $(SAMPLES)/coroutine_sample.cpp
	$(CXX) -c $(CFLAGS) $(SAMPLES)/coroutine_sample.cpp

framework_sample.o: $(SAMPLES)/framework_sample.cpp
	$(CXX) -c $(CFLAGS) $(SAMPLES)/framework_sample.cpp

bt_sample.o: $(SAMPLES)/bt_sample.cpp
	$(CXX) -c $(CFLAGS) $(SAMPLES)/bt_sample.cpp

BtParams.o: $(BEHTREE)/BtParams.cpp $(BEHTREE)/BtParams.h
	$(CXX) -c $(CFLAGS) $(BEHTREE)/BtParams.cpp

BtNode.o: $(BEHTREE)/BtNode.cpp $(BEHTREE)/BtNode.h
	$(CXX) -c $(CFLAGS) $(BEHTREE)/BtNode.cpp

BtSelectorNode.o: $(BEHTREE)/BtSelectorNode.cpp $(BEHTREE)/BtSelectorNode.h
	$(CXX) -c $(CFLAGS) $(BEHTREE)/BtSelectorNode.cpp

BtSequenceNode.o: $(BEHTREE)/BtSequenceNode.cpp $(BEHTREE)/BtSequenceNode.h
	$(CXX) -c $(CFLAGS) $(BEHTREE)/BtSequenceNode.cpp

BtParallelSucceedOnAllNode.o: $(BEHTREE)/BtParallelSucceedOnAllNode.cpp $(BEHTREE)/BtParallelSucceedOnAllNode.h
	$(CXX) -c $(CFLAGS) $(BEHTREE)/BtParallelSucceedOnAllNode.cpp

BtParallelFailOnAllNode.o: $(BEHTREE)/BtParallelFailOnAllNode.cpp $(BEHTREE)/BtParallelFailOnAllNode.h
	$(CXX) -c $(CFLAGS) $(BEHTREE)/BtParallelFailOnAllNode.cpp

BtParallelHybridNode.o: $(BEHTREE)/BtParallelHybridNode.cpp $(BEHTREE)/BtParallelHybridNode.h
	$(CXX) -c $(CFLAGS) $(BEHTREE)/BtParallelHybridNode.cpp

BtDecoratorNotNode.o: $(BEHTREE)/BtDecoratorNotNode.cpp $(BEHTREE)/BtDecoratorNotNode.h
	$(CXX) -c $(CFLAGS) $(BEHTREE)/BtDecoratorNotNode.cpp

BtDecoratorTimerNode.o: $(BEHTREE)/BtDecoratorTimerNode.cpp $(BEHTREE)/BtDecoratorTimerNode.h
	$(CXX) -c $(CFLAGS) $(BEHTREE)/BtDecoratorTimerNode.cpp

BtDecoratorCounterNode.o: $(BEHTREE)/BtDecoratorCounterNode.cpp $(BEHTREE)/BtDecoratorCounterNode.h
	$(CXX) -c $(CFLAGS) $(BEHTREE)/BtDecoratorCounterNode.cpp

BtDecoratorForNode.o: $(BEHTREE)/BtDecoratorForNode.cpp $(BEHTREE)/BtDecoratorForNode.h
	$(CXX) -c $(CFLAGS) $(BEHTREE)/BtDecoratorForNode.cpp

BtDecoratorUntilNode.o: $(BEHTREE)/BtDecoratorUntilNode.cpp $(BEHTREE)/BtDecoratorUntilNode.h
	$(CXX) -c $(CFLAGS) $(BEHTREE)/BtDecoratorUntilNode.cpp

BtBehaviorNode.o: $(BEHTREE)/BtBehaviorNode.cpp $(BEHTREE)/BtBehaviorNode.h
	$(CXX) -c $(CFLAGS) $(BEHTREE)/BtBehaviorNode.cpp

BtConditionNode.o: $(BEHTREE)/BtConditionNode.cpp $(BEHTREE)/BtConditionNode.h
	$(CXX) -c $(CFLAGS) $(BEHTREE)/BtConditionNode.cpp

BtActionNode.o: $(BEHTREE)/BtActionNode.cpp $(BEHTREE)/BtActionNode.h
	$(CXX) -c $(CFLAGS) $(BEHTREE)/BtActionNode.cpp

BtXmlGenerator.o: $(BEHTREE)/BtXmlGenerator.cpp $(BEHTREE)/BtXmlGenerator.h
	$(CXX) -c $(CFLAGS) $(BEHTREE)/BtXmlGenerator.cpp

RfAction.o: $(FRAMEWORK)/RfAction.cpp $(FRAMEWORK)/RfAction.h
	$(CXX) -c $(CFLAGS) $(FRAMEWORK)/RfAction.cpp

RfActionHandler.o: $(FRAMEWORK)/RfActionHandler.cpp $(FRAMEWORK)/RfActionHandler.h
	$(CXX) -c $(CFLAGS) $(FRAMEWORK)/RfActionHandler.cpp

RfRequestService.o: $(FRAMEWORK)/RfRequestService.cpp $(FRAMEWORK)/RfRequestService.h
	$(CXX) -c $(CFLAGS) $(FRAMEWORK)/RfRequestService.cpp

RfRunnableService.o: $(FRAMEWORK)/RfRunnableService.cpp $(FRAMEWORK)/RfRunnableService.h
	$(CXX) -c $(CFLAGS) $(FRAMEWORK)/RfRunnableService.cpp

RfService.o: $(FRAMEWORK)/RfService.cpp $(FRAMEWORK)/RfService.h
	$(CXX) -c $(CFLAGS) $(FRAMEWORK)/RfService.cpp

RfServiceManager.o: $(FRAMEWORK)/RfServiceManager.cpp $(FRAMEWORK)/RfServiceManager.h
	$(CXX) -c $(CFLAGS) $(FRAMEWORK)/RfServiceManager.cpp

Allocator.o: $(UTILS)/Memory/Allocator.cpp $(UTILS)/Memory/Allocator.h
	$(CXX) -c $(CFLAGS) $(UTILS)/Memory/Allocator.cpp

MemoryLeakDetector.o: $(UTILS)/Memory/MemoryLeakDetector.cpp $(UTILS)/Memory/MemoryLeakDetector.h
	$(CXX) -c $(CFLAGS) $(UTILS)/Memory/MemoryLeakDetector.cpp

Mutex.o: $(UTILS)/Thread/Mutex.cpp $(UTILS)/Thread/Mutex.h
	$(CXX) -c $(CFLAGS) $(UTILS)/Thread/Mutex.cpp

TypeInfo.o: $(UTILS)/Object/TypeInfo.cpp $(UTILS)/Object/TypeInfo.h
	$(CXX) -c $(CFLAGS) $(UTILS)/Object/TypeInfo.cpp

Coroutine.o: $(UTILS)/Thread/Coroutine.cpp $(UTILS)/Thread/Coroutine.h
	$(CXX) -c $(CFLAGS) $(UTILS)/Thread/Coroutine.cpp

clean:
	rm -f *.o $(OUTPUT)

.PHONY: all clean
