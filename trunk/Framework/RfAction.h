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

#ifndef __RangerFramework_RfAction_H__
#define __RangerFramework_RfAction_H__

#include "RfService.h"

class RfActionHandler;
class RfRequestService;

class RfAction : public RfService
{
public:
	friend class RfActionHandler;

	typedef ptrdiff_t ID;

public:
	RfAction();
	virtual ~RfAction();

	ID getActionID() const;

	void setHandler(RfActionHandler* handler);
	void setTimeout(long timeout);

	bool execute();

protected:
	void response(const void* params);

	virtual bool onExecute() = 0;
	virtual bool onResponse(const void* params);

	virtual bool onTick(long escape);

private:
	ID mActionID;
	RfActionHandler* mHandler;
	bool mIsActive;
	long mTimeout;
};

DeclareSmartPointer(RfAction);

#endif  // __RangerFramework_RfAction_H__
