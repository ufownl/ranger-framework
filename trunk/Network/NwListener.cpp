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

#include <event2/listener.h>
#include "NwListener.h"
#include <stdexcept>

NwListener::NwListener(evconnlistener* listener)
	: mBackend(listener)
{
	if (!listener)
	{
		throw std::invalid_argument("Invalid listener.");
	}
}

NwListener::~NwListener()
{
	if (mBackend)
	{
		evconnlistener_free(mBackend);
	}
}

evconnlistener* NwListener::backend() const
{
	return mBackend;
}
