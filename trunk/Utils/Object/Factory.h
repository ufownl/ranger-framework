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

#ifndef __Utils_Object_Factory_H__
#define __Utils_Object_Factory_H__

#include "Object/Singleton.h"
#include "Memory/STLAllocator.h"
#include <boost/unordered_map.hpp>
#include <stdexcept>
#include <utility>

template <class _id_type, class _creator>
class DefaultFactoryStorage
{
private:
	typedef boost::unordered_map<
		_id_type,
		_creator,
		boost::hash<_id_type>,
		std::equal_to<_id_type>,
		typename stl_alloc<std::pair<const _id_type, _creator> >::type
	> CallbackMap;

public:
	bool insert(const _id_type& id, _creator creator)
	{
		if (mCallbacks.count(id) > 0)
		{
			return false;
		}

		mCallbacks.insert(std::make_pair(id, creator));
		return true;
	}

	_creator& get(const _id_type& id)
	{
		typename CallbackMap::iterator it = mCallbacks.find(id);

		if (it == mCallbacks.end())
		{
			throw std::runtime_error("Function not found.");
		}

		return it->second;
	}

private:
	CallbackMap mCallbacks;
};

template <class _id_type, class _creator>
class FastFactoryStorage;

template <
	class _abs_base,
	class _id_type,
	class _creator = _abs_base* (*)(),
	template <class> class _thread_policy = ObjectLevelLockable,
	template <class, class> class _storage_policy = DefaultFactoryStorage
>
class Factory
	: public _thread_policy<
		Factory<
			_abs_base,
			_id_type,
			_creator,
			_thread_policy,
			_storage_policy
		>
	>
	, protected _storage_policy<
		_id_type,
		_creator
	>
{
public:
	typedef _thread_policy<
		Factory<
			_abs_base,
			_id_type,
			_creator,
			_thread_policy,
			_storage_policy
		>
	> ThreadPolicy;

	typedef _storage_policy<
		_id_type,
		_creator
	> StoragePolicy;

public:
	bool regist(const _id_type& id, _creator creator)
	{
		typename ThreadPolicy::Lock l(*this);
		ScopedLock<typename ThreadPolicy::Lock> sl(l);
		return StoragePolicy::insert(id, creator);
	}

	_abs_base* create(const _id_type& id)
	{
		try
		{
			typename ThreadPolicy::Lock l(*this);
			ScopedLock<typename ThreadPolicy::Lock> sl(l);
			return StoragePolicy::get(id)();
		}
		catch (std::runtime_error&)
		{
			return 0;
		}
	}
};

#define FAST_FACTORY_STORAGE(_id_type, _size)	\
	template <class _creator>	\
	class FastFactoryStorage<_id_type, _creator>	\
	{	\
	private:	\
		struct creator_info_t	\
		{	\
			_creator creator;	\
			bool regist;	\
		};	\
	public:	\
		FastFactoryStorage()	\
		{	\
			for (size_t i = 0; i < _size; ++i)	\
			{	\
				mCallbacks[i].regist = false;	\
			}	\
		}	\
		bool insert(_id_type id, _creator creator)	\
		{	\
			if (mCallbacks[id].regist)	\
			{	\
				return false;	\
			}	\
			mCallbacks[id].creator = creator;	\
			mCallbacks[id].regist = true;	\
			return true;	\
		}	\
		_creator& get(_id_type id)	\
		{	\
			if (!mCallbacks[id].regist)	\
			{	\
				throw std::runtime_error("Function not found.");	\
			}	\
			return mCallbacks[id].creator;	\
		}	\
	private:	\
		creator_info_t mCallbacks[_size];	\
	};

FAST_FACTORY_STORAGE(unsigned short, 0x10000)
FAST_FACTORY_STORAGE(unsigned char, 0x100)

#endif  // __Utils_Object_Factory_H__
