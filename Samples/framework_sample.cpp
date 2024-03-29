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

#include "RfRequestService.h"
#include "RfServiceManager.h"
#include "RfActionHandler.h"
#include <queue>
#include <iostream>
#include <assert.h>

size_t gCount = 0;

class MyResponseService : public RfRequestService
{
public:
	~MyResponseService()
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	void push(RfAction::ID id)
	{
		mQue.push(id);
	}

protected:
	virtual bool onInitialize()
	{
		if (!RfRequestService::onInitialize())
		{
			return false;
		}

		std::cout << "MyResponseService::onInitialize" << std::endl;

		return true;
	}

	virtual bool onTick(long escape)
	{
		if (!RfRequestService::onTick(escape))
		{
			return false;
		}

		for ( ; !mQue.empty(); mQue.pop())
		{
			getActionHandler()->response(mQue.front(), 0);
		}

		if (std::cin.get() == 'q')
		{
			return false;
		}

		std::cout << gCount << std::endl;

		return true;
	}

	virtual void onShutdown()
	{
		std::cout << "MyResponseService::onShutdown" << std::endl;
	}

private:
	std::queue<RfAction::ID> mQue;
};

class MyAction : public RfAction
{
public:
	MyAction()
		: mIndex(msCounter++)
	{
		setTimeout(5000);

		++gCount;
		std::cout << "construct " << getActionID() << " " << mIndex << std::endl;
	}

	~MyAction()
	{
		--gCount;
		std::cout << "destruct " << getActionID() << " " << mIndex << std::endl;
	}

protected:
	virtual bool onExecute()
	{
		std::cout << "onExecute " << getActionID() << " " << mIndex << std::endl;
		return true;
	}

	virtual bool onResponse(const void* params)
	{
		std::cout << "onResponse " << getActionID() << " " << mIndex << std::endl;
		return true;
	}

private:
	size_t mIndex;
	static size_t msCounter;
};

size_t MyAction::msCounter = 0;

class MyRequestService : public RfRequestService
{
public:
	~MyRequestService()
	{
		std::cout << __FUNCTION__ << std::endl;
	}

protected:
	virtual bool onInitialize()
	{
		if (!RfRequestService::onInitialize())
		{
			return false;
		}
		
		mService = getManager()->get<MyResponseService>();
		assert(mService);

		std::cout << "MyRequestService::onInitialize" << std::endl;

		return true;
	}

	virtual bool onTick(long escape)
	{
		if (!RfRequestService::onTick(escape))
		{
			return false;
		}

		SmartPointer<MyAction> action;

		for (int i = 0; i < 4; ++i)
		{
			action = RfNew MyAction;
			action->setHandler(getActionHandler());
			if (action->execute())
			{
				std::cout << "execute " << action->getActionID() << std::endl;
				mService->push(action->getActionID());
			}
		}

		return true;
	}

	virtual void onShutdown()
	{
		std::cout << "MyRequestService::onShutdown" << std::endl;
	}

private:
	MyResponseService* mService;
};

int main()
{
	RfServiceManager mgr;

	mgr.append(RfNew RfActionHandler(3));
	mgr.append(RfNew MyResponseService);
	mgr.append(RfNew MyRequestService);

	mgr.run();

	return 0;
}
