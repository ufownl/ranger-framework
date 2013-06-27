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

#include <cppunit/extensions/HelperMacros.h>
#include <luabind/luabind.hpp>
#include "BtConditionNode.h"
#include "BtActionNode.h"
#include "BtParams.h"
#include "BtXmlGenerator.h"

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define MyExtra_Alloc	TCMallocAllocator
#else
#define MyExtra_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class BtDecoratorNodeTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(BtDecoratorNodeTest);
	CPPUNIT_TEST(testBtDecoratorNotNode);
	CPPUNIT_TEST_SUITE_END();

public:
	class MyExtra : public RefObject<MyExtra_Alloc, unsigned int, SingleThread>
	{
	public:
		MyExtra()
			: mCount(0)
		{
		}

		void setCount(size_t count)
		{
			mCount = count;
		}

		size_t getCount() const
		{
			return mCount;
		}

		void call()
		{
			++mCount;
		}

	private:
		size_t mCount;
	};

	class MyConditionNode : public BtConditionNode
	{
	protected:
		virtual void defineExtraData()
		{
			luabind::module(getLua())
			[
				luabind::class_<MyExtra>("MyExtra")
					.def("call", &MyExtra::call)
			];
		}

		virtual void exportExtraData(void* extra)
		{
			luabind::globals(getLua())["extra"] = static_cast<MyExtra*>(extra);
		}
	};

	class MyActionNode : public BtActionNode
	{
	protected:
		virtual void defineExtraData()
		{
			luabind::module(getLua())
			[
				luabind::class_<MyExtra>("MyExtra")
					.def("getCount", &MyExtra::getCount)
					.def("call", &MyExtra::call)
			];
		}

		virtual void exportExtraData(void* extra)
		{
			luabind::globals(getLua())["extra"] = static_cast<MyExtra*>(extra);
		}
	};

public:
	virtual void setUp()
	{
	}

	virtual void tearDown()
	{
	}

private:
	void testBtDecoratorNotNode()
	{
		BtParamsPtr params = RfNew BtParams(32);

		BtNodePtr root = BtXmlGenerator::generate("./BehaviorTree/bt_not_t.xml");
		CPPUNIT_ASSERT(root);
		CPPUNIT_ASSERT(!root->execute(params));

		root = BtXmlGenerator::generate("./BehaviorTree/bt_not_f.xml");
		CPPUNIT_ASSERT(root);
		CPPUNIT_ASSERT(root->execute(params));
	}
};

template <>
struct BtNodeTraits<BtDecoratorNodeTest::MyConditionNode>
{
	static const char* name()
	{
		return "BtDecoratorNodeTest::MyConditionNode";
	}
};

template <>
struct BtNodeTraits<BtDecoratorNodeTest::MyActionNode>
{
	static const char* name()
	{
		return "BtDecoratorNodeTest::MyActionNode";
	}
};

static BtNodeFactoryRegister<BtDecoratorNodeTest::MyConditionNode> gsConditionReg;
static BtNodeFactoryRegister<BtDecoratorNodeTest::MyActionNode> gsActionReg;

CPPUNIT_TEST_SUITE_REGISTRATION(BtDecoratorNodeTest);

