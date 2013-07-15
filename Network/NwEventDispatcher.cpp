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

#include <event2/event.h>
#include "NwEventDispatcher.h"
#include <stdio.h>

NwEventDispatcher::NwEventDispatcher(int cpus /* = 0 */)
	: mInitializer(NwInitializer::getSingletonPtr())
	, mBackend(0)
{
	if (!mInitializer)
	{
		try
		{
			mInitializer = RfNew NwInitializer;
		}
		catch (const std::logic_error& e)
		{
			fprintf(stderr, "logic_error: %s\n", e.what());
			mInitializer = NwInitializer::getSingletonPtr();
		}
	}

	event_config* cfg = event_config_new();

	if (!cfg)
	{
		throw std::bad_alloc();
	}

#if defined(_WIN32) || defined(_WIN64)
	if (cpus > 0)
	{
		event_config_set_flag(cfg, EVENT_BASE_FLAG_STARTUP_IOCP);
		event_config_set_num_cpus_hint(cfg, cpus);
	}
#endif  // _WIN32 || _WIN64

	mBackend = event_base_new_with_config(cfg);

	if (!mBackend)
	{
		event_config_free(cfg);
		throw std::bad_alloc();
	}

	event_config_free(cfg);
}

NwEventDispatcher::~NwEventDispatcher()
{
	if (mBackend)
	{
		event_base_free(mBackend);
	}
}

int NwEventDispatcher::dispatch()
{
	return event_base_dispatch(mBackend);
}

int NwEventDispatcher::dispatchOnce(bool block /* = true */)
{
	if (block)
	{
		return event_base_loop(mBackend, EVLOOP_ONCE);
	}
	else
	{
		return event_base_loop(mBackend, EVLOOP_ONCE | EVLOOP_NONBLOCK);
	}
}

void NwEventDispatcher::exit(float sec /* = 0.0f */)
{
	if (sec == 0.0f)
	{
		event_base_loopexit(mBackend, 0);
	}
	else
	{
		timeval tv;

		tv.tv_sec = static_cast<long>(sec);
		tv.tv_usec = static_cast<long>((sec - tv.tv_sec) * 1000000);

		event_base_loopexit(mBackend, &tv);
	}
}

void NwEventDispatcher::quit()
{
	event_base_loopbreak(mBackend);
}

event_base* NwEventDispatcher::backend() const
{
	return mBackend;
}
