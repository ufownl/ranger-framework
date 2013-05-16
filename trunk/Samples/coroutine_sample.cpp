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

#include "Thread/Coroutine.h"
#include <stdio.h>

void permgen(int *a, size_t n)
{
	if (n == 0)
	{
		Coroutine::yield<void>(a);
	}
	else
	{
		for (size_t i = 0; i < n; ++i)
		{
			std::swap(a[i], a[n - 1]);
			permgen(a, n - 1);
			std::swap(a[i], a[n - 1]);
		}
	}
}

void permgen_sample()
{
	putchar('\n');
	puts(__FUNCTION__);
	putchar('\n');

	int a[3] = {1, 2, 3};
	CoroutinePtr co = RfNew Coroutine(boost::bind(permgen, a, 3));

	for (int *p = co->resume<int*>(); co->status() != Coroutine::eDEAD; p = co->resume<int*>())
	{
		for (size_t i = 0; i < 3; ++i)
		{
			printf("%d ", p[i]);
		}
		putchar('\n');
	}
}

#define LINE_SIZE	1024

const char* receive(Coroutine *co)
{
	return co->resume<const char*>();
}

void send(const char *line)
{
	Coroutine::yield<void>(line);
}

void producer()
{
	char buf[LINE_SIZE];

	for (char *line = gets(buf); line; line = gets(buf))
	{
		send(line);
	}

	send("EOF");
}

void filter(CoroutinePtr co)
{
	size_t idx = 0;

	for (const char *line = receive(co); co->status() != Coroutine::eDEAD; line = receive(co))
	{
		char buf[LINE_SIZE + 6];

		sprintf(buf, "%5lu %s", ++idx, line);
		send(buf);
	}
}

void consumer(CoroutinePtr co)
{
	for (const char *line = receive(co); co->status() != Coroutine::eDEAD; line = receive(co))
	{
		puts(line);
	}
}

void producer_consumer_sample()
{
	putchar('\n');
	puts(__FUNCTION__);
	putchar('\n');

	consumer(RfNew Coroutine(boost::bind(filter, RfNew Coroutine(producer))));
}

int main()
{
	permgen_sample();
	producer_consumer_sample();
	return 0;
}
