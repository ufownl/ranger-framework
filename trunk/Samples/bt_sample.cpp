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

#include "BtConditionNode.h"
#include "BtActionNode.h"
#include "BtParams.h"
#include "BtXmlGenerator.h"
#include <luabind/luabind.hpp>
#include <iostream>
#include <string>

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define MyExtra_Alloc	TCMallocAllocator
#else
#define MyExtra_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class MyExtra : public RefObject<MyExtra_Alloc>
{
public:
	MyExtra(const std::string& msg)
		: mMsg(msg)
	{
	}

	void func(const char* msg)
	{
		std::cout << mMsg << std::endl;
		std::cout << msg << std::endl;
	}

private:
	std::string mMsg;
};

DeclareSmartPointer(MyExtra);

class MyConditionNode : public BtConditionNode
{
protected:
	virtual void defineExtraData()
	{
		luabind::module(getLua())
		[
			luabind::class_<MyExtra>("MyExtra")
				.def("func", &MyExtra::func)
		];
	}

	virtual void exportExtraData(void* extra)
	{
		luabind::globals(getLua())["extra"] = static_cast<MyExtra*>(extra);
	}
};

template <>
struct BtNodeTraits<MyConditionNode>
{
	static const char* name()
	{
		return "MyConditionNode";
	}
};

static BtNodeFactoryRegister<MyConditionNode> gsConditionReg;

class MyActionNode : public BtActionNode
{
protected:
	virtual void defineExtraData()
	{
		luabind::module(getLua())
		[
			luabind::class_<MyExtra>("MyExtra")
				.def("func", &MyExtra::func)
		];
	}

	virtual void exportExtraData(void* extra)
	{
		luabind::globals(getLua())["extra"] = static_cast<MyExtra*>(extra);
	}
};

template <>
struct BtNodeTraits<MyActionNode>
{
	static const char* name()
	{
		return "MyActionNode";
	}
};

static BtNodeFactoryRegister<MyActionNode> gsActionReg;

int main()
{
	BtParamsPtr params = RfNew BtParams(32);
	BtNodePtr root = BtXmlGenerator::generate("./bt_hello.xml");

	if (root)
	{
		MyExtraPtr extra = RfNew MyExtra("BehaviorTree Hello Sample");

		params->setExtraData(extra);
		while (root->execute(params)) ;
	}

	return 0;
}
