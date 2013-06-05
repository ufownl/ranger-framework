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

#ifndef __Utils_Object_TypeInfo_H__
#define __Utils_Object_TypeInfo_H__

#include <typeinfo>
#include <boost/functional/hash.hpp>

class TypeInfo
{
public:
	TypeInfo();
	TypeInfo(const std::type_info& info);
	TypeInfo(const TypeInfo& info);

	TypeInfo& operator = (const TypeInfo& rhs);

	const char* name() const;
	size_t hash_code() const;

	const std::type_info& data() const;

private:
	const std::type_info* mInfo;
};

bool operator == (const TypeInfo& lhs, const TypeInfo& rhs);
bool operator != (const TypeInfo& lhs, const TypeInfo& rhs);
bool operator < (const TypeInfo& lhs, const TypeInfo& rhs);

namespace boost
{

	template <>
	struct hash<TypeInfo> : public std::unary_function<TypeInfo, size_t>
	{
		size_t operator () (const TypeInfo& v) const
		{
			return v.hash_code();
		}
	};

}

#endif  // __Utils_Object_TypeInfo_H__
