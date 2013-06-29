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

#ifndef __Network_NwEventHandler_H__
#define __Network_NwEventHandler_H__

class NwConnection;
class NwBufferBase;

class NwEventHandler
{
public:
	virtual ~NwEventHandler();

	virtual void onAccept(NwConnection* conn);
	virtual void onConnect(NwConnection* conn);
	virtual void onRead(NwConnection* conn, NwBufferBase* buf) = 0;
	virtual void onError(NwConnection* conn, const char* err);
	virtual void onTimeout(NwConnection* conn);
	virtual void onEof(NwConnection* conn);
};

#endif  // __Network_NwEventHandler_H__
