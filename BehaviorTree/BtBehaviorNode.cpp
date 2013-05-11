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

#include "BtBehaviorNode.h"
#include "BtParams.h"
#include <luabind/luabind.hpp>

VISITABLE_IMPL(BtBehaviorNode, BtGenerator)

BtBehaviorNode::BtBehaviorNode()
	: mLua(0)
{
}

BtBehaviorNode::~BtBehaviorNode()
{
	if (mLua)
	{
		lua_close(mLua);
	}
}

void BtBehaviorNode::setScript(const char* script)
{
	mScript = script;
}

void BtBehaviorNode::addParam(const char* name, double val)
{
	mParams.push_back(std::make_pair(name, val));
}

bool BtBehaviorNode::execute(BtParams* params)
{
	if (!mLua && !initialize())
	{
		return false;
	}

	exportExtraData(params->getExtraData());

	return doBehavior();
}

void BtBehaviorNode::exportParams()
{
	for (BtParamTable::iterator i = mParams.begin(); i != mParams.end(); ++i)
	{
		luabind::globals(mLua)[i->first] = i->second;
	}
}

bool BtBehaviorNode::initialize()
{
	mLua = luaL_newstate();

	if (!mLua)
	{
		return false;
	}

	luaL_openlibs(mLua);
	luabind::open(mLua);

	defineExtraData();
	exportParams();

	luaL_dofile(mLua, mScript.c_str());

	return true;
}
