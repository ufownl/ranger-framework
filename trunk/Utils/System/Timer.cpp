/*	Copyright 2013 RangerUFO
 *
 *	This file is part of RangerFramework.
 *
 *	RangerFramework is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	RangerFramework is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU Lesser General Public License for more details.
 *
 *	You should have received a copy of the GNU Lesser General Public License
 *	along with RangerFramework.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "System/Timer.h"
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#elif defined(__linux__)
#include <time.h>
#include <unistd.h>
#else
#include <unistd.h>
#include <sys/time.h>
#endif  // _WIN32 || _WIN64

unsigned int RfClock()
{
#if defined(_WIN32) || defined(_WIN64)
	return GetTickCount();
#elif defined(__linux__)
	timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
#else
	struct timeval tv;
	gettimeofday(&tv, 0);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000000;
#endif  // _WIN32 || _WIN64
}

void RfSleep(unsigned msec)
{
#if defined(_WIN32) || defined(_WIN64)
	Sleep(msec);
#else
	usleep(msec * 1000);
#endif  // _WIN32 || _WIN64
}
