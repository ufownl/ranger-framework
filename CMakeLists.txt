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

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(RANGER)

IF(NOT WIN32)
	SET(BUILD_SHARED_LIBS ON)
ENDIF(NOT WIN32)

ADD_SUBDIRECTORY(Utils)
ADD_SUBDIRECTORY(Framework)
ADD_SUBDIRECTORY(BehaviorTree)
ADD_SUBDIRECTORY(Network)
ADD_SUBDIRECTORY(AutoRecast)
ADD_SUBDIRECTORY(test)
ADD_SUBDIRECTORY(Samples)
