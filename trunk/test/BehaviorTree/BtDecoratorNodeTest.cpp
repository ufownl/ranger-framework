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
#include "System/Timer.h"
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
	CPPUNIT_TEST(testBtDecoratorCounterNode);
	CPPUNIT_TEST(testBtDecoratorForNode);
	CPPUNIT_TEST(testBtDecoratorUntilNode);
	CPPUNIT_TEST(testBtDecoratorTimerNode);
	CPPUNIT_TEST_SUITE_END();

public:
	class MyExtra : public RefObject<MyExtra_Alloc>
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

	void testBtDecoratorCounterNode()
	{
		BtParamsPtr params = RfNew BtParams(32);
		SmartPointer<MyExtra> extra = RfNew MyExtra;
		params->setExtraData(extra);

		BtNodePtr root = BtXmlGenerator::generate("./BehaviorTree/bt_counter_5_0_t.xml");
		CPPUNIT_ASSERT(root);
		for (int i = 0; i < 10; ++i)
		{
			if (i < 5)
			{
				CPPUNIT_ASSERT(root->execute(params));
			}
			else
			{
				CPPUNIT_ASSERT(!root->execute(params));
			}
		}
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(5), extra->getCount());
		extra->setCount(0);
	}

	void testBtDecoratorForNode()
	{
		BtParamsPtr params = RfNew BtParams(32);
		SmartPointer<MyExtra> extra = RfNew MyExtra;
		params->setExtraData(extra);

		BtNodePtr root = BtXmlGenerator::generate("./BehaviorTree/bt_for_10_l5.xml");
		CPPUNIT_ASSERT(root);
		CPPUNIT_ASSERT(root->execute(params));
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(10), extra->getCount());
		extra->setCount(0);
		
		root = BtXmlGenerator::generate("./BehaviorTree/bt_for_10_l-5.xml");
		CPPUNIT_ASSERT(root);
		CPPUNIT_ASSERT(!root->execute(params));
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(10), extra->getCount());
		extra->setCount(0);
	}

	void testBtDecoratorUntilNode()
	{
		BtParamsPtr params = RfNew BtParams(32);
		SmartPointer<MyExtra> extra = RfNew MyExtra;
		params->setExtraData(extra);

		BtNodePtr root = BtXmlGenerator::generate("./BehaviorTree/bt_until_f_10_l5.xml");
		CPPUNIT_ASSERT(root);
		CPPUNIT_ASSERT(root->execute(params));
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(5), extra->getCount());
		extra->setCount(0);

		root = BtXmlGenerator::generate("./BehaviorTree/bt_until_f_10_l11.xml");
		CPPUNIT_ASSERT(root);
		CPPUNIT_ASSERT(!root->execute(params));
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(10), extra->getCount());
		extra->setCount(0);
	}

	void testBtDecoratorTimerNode()
	{
		BtParamsPtr params = RfNew BtParams(32);

		BtNodePtr root = BtXmlGenerator::generate("./BehaviorTree/bt_timer_1_0_t.xml");
		CPPUNIT_ASSERT(root);
		CPPUNIT_ASSERT(root->execute(params));
		RfSleep(100);
		CPPUNIT_ASSERT(!root->execute(params));
		RfSleep(1000);
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

