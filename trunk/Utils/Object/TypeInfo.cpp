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

#include "Object/TypeInfo.h"
#include <assert.h>

TypeInfo::TypeInfo()
	: mInfo(0)
{
}

TypeInfo::TypeInfo(const std::type_info& info)
	: mInfo(&info)
{
}

TypeInfo::TypeInfo(const TypeInfo& info)
	: mInfo(info.mInfo)
{
}

TypeInfo& TypeInfo::operator = (const TypeInfo& rhs)
{
	mInfo = rhs.mInfo;
	return *this;
}

bool TypeInfo::operator == (const TypeInfo& rhs) const
{
	assert(mInfo);
	assert(rhs.mInfo);
	return *mInfo == *rhs.mInfo;
}

bool TypeInfo::operator != (const TypeInfo& rhs) const
{
	assert(mInfo);
	assert(rhs.mInfo);
	return *mInfo != *rhs.mInfo;
}

bool TypeInfo::operator < (const TypeInfo& rhs) const
{
	assert(mInfo);
	assert(rhs.mInfo);
	return mInfo->before(*rhs.mInfo);
}

const char* TypeInfo::name() const
{
	assert(mInfo);
	return mInfo->name();
}
