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

all: Prepare Utils Framework BehaviorTree Samples test

Prepare:
	mkdir -p lib
	mkdir -p obj/debug
	mkdir -p obj/release

Utils:
	make -C Utils

Framework:
	make -C Framework

BehaviorTree:
	make -C BehaviorTree

Samples:
	make -C Samples

test:
	make -C test

clean:
	make -C test clean
	make -C Samples clean
	make -C BehaviorTree clean
	make -C Framework clean
	make -C Utils clean
	-rmdir lib
	-rmdir obj/debug
	-rmdir obj/release
	-rmdir obj

.PHONY: all Prepare Utils Framework BehaviorTree Samples test clean
