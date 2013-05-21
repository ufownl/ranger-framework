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
    SmartPointer(T *object = (T*)0);
    SmartPointer(const SmartPointer &ptr);
    ~SmartPointer();

    operator T* () const;
    T* data() const;

    T& operator * () const;
    T* operator -> () const;

    SmartPointer<T>& operator = (const SmartPointer<T> &ptr);
    SmartPointer<T>& operator = (T *object);

    bool operator == (T *object) const;
    bool operator != (T *object) const;
    bool operator == (const SmartPointer<T> &ptr) const;
    bool operator != (const SmartPointer<T> &ptr) const;
    bool operator < (T *object) const;
    bool operator > (T *object) const;
    bool operator < (const SmartPointer<T> &ptr) const;
    bool operator > (const SmartPointer<T> &ptr) const;
    bool operator <= (T *object) const;
    bool operator >= (T *object) const;
    bool operator <= (const SmartPointer<T> &ptr) const;
    bool operator >= (const SmartPointer<T> &ptr) const;

    void swap(SmartPointer<T> &otherPtr);

private:
    T *mObject;
};


#define DeclareSmartPointer(classname) \
    class classname; \
    typedef SmartPointer<classname> classname##Ptr


template <class T>
SmartPointer<T>::SmartPointer(T *object/* = (T*)0 */)
    : mObject(object)
{
    if (mObject) mObject->incRefCount();
}

template <class T>
SmartPointer<T>::SmartPointer(const SmartPointer &ptr)
    : mObject(ptr.mObject)
{
    if (mObject) mObject->incRefCount();
}

template <class T>
SmartPointer<T>::~SmartPointer()
{
    if (mObject) mObject->decRefCount();
}

template <class T>
SmartPointer<T>::operator T* () const
{
    return mObject;
}

template <class T>
T* SmartPointer<T>::data() const
{
    return mObject;
}

template <class T>
T& SmartPointer<T>::operator * () const
{
    return *mObject;
}

template <class T>
T* SmartPointer<T>::operator -> () const
{
    return mObject;
}

template <class T>
SmartPointer<T>& SmartPointer<T>::operator = (const SmartPointer<T> &ptr)
{
    if (mObject != ptr.mObject)
    {
        if (mObject) mObject->decRefCount();
        mObject = ptr.mObject;
        if (mObject) mObject->incRefCount();
    }
    return *this;
}

template <class T>
SmartPointer<T>& SmartPointer<T>::operator = (T *object)
{
    if (mObject != object)
    {
        if (mObject) mObject->decRefCount();
        mObject = object;
        if (mObject) mObject->incRefCount();
    }
    return *this;
}

template <class T>
bool SmartPointer<T>::operator == (T *object) const
{
    return mObject == object;
}

template <class T>
bool SmartPointer<T>::operator != (T *object) const
{
    return mObject != object;
}

template <class T>
bool SmartPointer<T>::operator == (const SmartPointer<T> &ptr) const
{
    return mObject == ptr.mObject;
}

template <class T>
bool SmartPointer<T>::operator != (const SmartPointer<T> &ptr) const
{
    return mObject != ptr.mObject;
}

template <class T>
bool SmartPointer<T>::operator < (T *object) const
{
    return mObject < object;
}

template <class T>
bool SmartPointer<T>::operator > (T *object) const
{
    return mObject > object;
}

template <class T>
bool SmartPointer<T>::operator < (const SmartPointer<T> &ptr) const
{
    return mObject < ptr.mObject;
}

template <class T>
bool SmartPointer<T>::operator > (const SmartPointer<T> &ptr) const
{
    return mObject > ptr.mObject;
}

template <class T>
bool SmartPointer<T>::operator <= (T *object) const
{
    return mObject <= object;
}

template <class T>
bool SmartPointer<T>::operator >= (T *object) const
{
    return mObject >= object;
}

template <class T>
bool SmartPointer<T>::operator <= (const SmartPointer<T> &ptr) const
{
    return mObject <= ptr.mObject;
}

template <class T>
bool SmartPointer<T>::operator >= (const SmartPointer<T> &ptr) const
{
    return mObject >= ptr.mObject;
}

template <class T>
void SmartPointer<T>::swap(SmartPointer<T> &otherPtr)
{
    T* temp = mObject;

    mObject = otherPtr.mObject;
    otherPtr.mObject = temp;
}

namespace std
{

	template <class T>
	void swap(SmartPointer<T>& ptr0, SmartPointer<T>& ptr1)
	{
		ptr0.swap(ptr1);
	}

}

#endif  // __Utils_Object_SmartPointer_H__
