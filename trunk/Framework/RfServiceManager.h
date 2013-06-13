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

#ifndef __RangerFramework_RfServiceManager_H__
#define __RangerFramework_RfServiceManager_H__

#include "RfRunnableService.h"
#include "Object/Singleton.h"
#include "Memory/STLAllocator.h"
#include <boost/type_traits.hpp>
#include <list>
#include <typeinfo>

class RfServiceManager : public RfRunnableService
{
public:
	typedef std::list<RfServicePtr, stl_alloc<RfServicePtr>::type> RfServiceList;

public:
	RfServiceManager(long period = 100);
	virtual ~RfServiceManager();

	void append(RfServicePtr service);
	void prepend(RfServicePtr service);
	RfServiceList::iterator insert(RfServiceList::iterator pos, RfServicePtr service);
	RfServiceList::iterator remove(RfServiceList::iterator pos);

	template <class T>
	RfServiceList::iterator remove()
	{
		BOOST_STATIC_ASSERT((boost::is_base_of<RfService, T>::value));

		RfServiceList::iterator it = find<T>();

		if (it == mServices.end())
		{
			return it;
		}

		return remove(it);
	}

	template <class T>
	RfServiceList::iterator find()
	{
		BOOST_STATIC_ASSERT((boost::is_base_of<RfService, T>::value));

		for (RfServiceList::iterator i = mServices.begin(); i != mServices.end(); ++i)
		{
			if (typeid(T) == typeid(**i))
			{
				return i;
			}
		}

		return mServices.end();
	}

	template <class T>
	T* get()
	{
		RfServiceList::iterator it = find<T>();

		if (it == mServices.end())
		{
			return 0;
		}

		return static_cast<T*>(it->data());
	}

	RfServiceList::iterator nil();

protected:
	virtual bool onTick(long escape);
	virtual void onShutdown();

private:
	RfServiceList mServices;
};

DeclareSmartPointer(RfServiceManager);

#endif  // __RangerFramework_RfServiceManager_H__
