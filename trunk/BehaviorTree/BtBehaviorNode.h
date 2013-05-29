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

#ifndef __BehaviorTree_BtBehaviorNode_H__
#define __BehaviorTree_BtBehaviorNode_H__

#include "BtNode.h"
#include "Memory/STLAllocator.h"
#include <lua.hpp>
#include <string>
#include <vector>
#include <utility>

class BtBehaviorNode : public BtNode
{
public:
	VISITABLE_DECL(BtGenerator)

public:
	BtBehaviorNode();
	virtual ~BtBehaviorNode();

	void setScript(const char* script);
	void addParam(const char* name, double val);

	virtual bool execute(BtParams* params);

protected:
	virtual void defineExtraData() = 0;
	virtual void exportExtraData(void* extra) = 0;
	virtual bool doBehavior() = 0;

	void exportParams();
	bool initialize();

	lua_State* getLua();

private:
	typedef std::vector<
		std::pair<std::string, double>,
		stl_alloc<std::pair<std::string, double> >::type
	> BtParamTable;

	lua_State* mLua;
	std::string mScript;
	BtParamTable mParams;
};

DeclareSmartPointer(BtBehaviorNode);

template <>
struct BtNodeTraits<BtBehaviorNode>
{
	static const char* name()
	{
		return "BtBehaviorNode";
	}
};

#endif  // __BehaviorTree_BtBehaviorNode_H__
