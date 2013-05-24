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

#ifndef __Utils_Object_SmartPointer_H__
#define __Utils_Object_SmartPointer_H__

template <class T>
class SmartPointer
{
public:
    SmartPointer(T* object = (T*)0)
		: mObject(object)
	{
		if (mObject)
		{
			mObject->incRefCount();
		}
	}

    SmartPointer(const SmartPointer<T>& rhs)
		: mObject(rhs.mObject)
	{
		if (mObject)
		{
			mObject->incRefCount();
		}
	}

    ~SmartPointer()
	{
		if (mObject)
		{
			mObject->decRefCount();
		}
	}

    operator T* () const
	{
		return mObject;
	}

    T* data() const
	{
		return mObject;
	}

    T& operator * () const
	{
		return *mObject;
	}

    T* operator -> () const
	{
		return mObject;
	}

    SmartPointer<T>& operator = (const SmartPointer<T>& rhs)
	{
		if (mObject != rhs.mObject)
		{
			if (mObject)
			{
				mObject->decRefCount();
			}

			mObject = rhs.mObject;

			if (mObject)
			{
				mObject->incRefCount();
			}
		}

		return *this;
	}

    void swap(SmartPointer<T>& rhs)
	{
		T* temp = mObject;
		mObject = rhs.mObject;
		rhs.mObject = temp;
	}

private:
    T* mObject;
};


#define DeclareSmartPointer(classname) \
    class classname; \
    typedef SmartPointer<classname> classname##Ptr


template <class T>
bool operator == (const SmartPointer<T>& lhs, const SmartPointer<T>& rhs)
{
	return lhs.data() == rhs.data();
}

template <class T>
bool operator != (const SmartPointer<T>& lhs, const SmartPointer<T>& rhs)
{
	return lhs.data() != rhs.data();
}

template <class T>
bool operator < (const SmartPointer<T>& lhs, const SmartPointer<T>& rhs)
{
	return lhs.data() < rhs.data();
}

template <class T>
bool operator > (const SmartPointer<T>& lhs, const SmartPointer<T>& rhs)
{
	return lhs.data() > rhs.data();
}

template <class T>
bool operator <= (const SmartPointer<T>& lhs, const SmartPointer<T>& rhs)
{
	return lhs.data() <= rhs.data();
}

template <class T>
bool operator >= (const SmartPointer<T>& lhs, const SmartPointer<T>& rhs)
{
	return lhs.data() >= rhs.data();
}

namespace std
{

	template <class T>
	void swap(SmartPointer<T>& lhs, SmartPointer<T>& rhs)
	{
		lhs.swap(rhs);
	}

}

#endif  // __Utils_Object_SmartPointer_H__
