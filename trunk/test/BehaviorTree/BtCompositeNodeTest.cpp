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

class BtCompositeNodeTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(BtCompositeNodeTest);
	CPPUNIT_TEST(testBtSelectorNode);
	CPPUNIT_TEST(testBtSequenceNode);
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
	void testBtSelectorNode()
	{
		BtParamsPtr params = RfNew BtParams(32);
		SmartPointer<MyExtra> extra = RfNew MyExtra;
		params->setExtraData(extra);

		BtNodePtr root = BtXmlGenerator::generate("./BehaviorTree/bt_selector_fff.xml");
		CPPUNIT_ASSERT(root);
		CPPUNIT_ASSERT(!root->execute(params));
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), extra->getCount());
		extra->setCount(0);

		root = BtXmlGenerator::generate("./BehaviorTree/bt_selector_tff.xml");
		CPPUNIT_ASSERT(root);
		CPPUNIT_ASSERT(root->execute(params));
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), extra->getCount());
		extra->setCount(0);

		root = BtXmlGenerator::generate("./BehaviorTree/bt_selector_ftf.xml");
		CPPUNIT_ASSERT(root);
		CPPUNIT_ASSERT(root->execute(params));
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), extra->getCount());
		extra->setCount(0);

		root = BtXmlGenerator::generate("./BehaviorTree/bt_selector_fft.xml");
		CPPUNIT_ASSERT(root);
		CPPUNIT_ASSERT(root->execute(params));
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), extra->getCount());
		extra->setCount(0);
	}

	void testBtSequenceNode()
	{
		BtParamsPtr params = RfNew BtParams(32);
		SmartPointer<MyExtra> extra = RfNew MyExtra;
		params->setExtraData(extra);

		BtNodePtr root = BtXmlGenerator::generate("./BehaviorTree/bt_sequence_ttt.xml");
		CPPUNIT_ASSERT(root);
		CPPUNIT_ASSERT(root->execute(params));
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), extra->getCount());
		extra->setCount(0);

		root = BtXmlGenerator::generate("./BehaviorTree/bt_sequence_ftt.xml");
		CPPUNIT_ASSERT(root);
		CPPUNIT_ASSERT(!root->execute(params));
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), extra->getCount());
		extra->setCount(0);

		root = BtXmlGenerator::generate("./BehaviorTree/bt_sequence_tft.xml");
		CPPUNIT_ASSERT(root);
		CPPUNIT_ASSERT(!root->execute(params));
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), extra->getCount());
		extra->setCount(0);

		root = BtXmlGenerator::generate("./BehaviorTree/bt_sequence_ttf.xml");
		CPPUNIT_ASSERT(root);
		CPPUNIT_ASSERT(!root->execute(params));
		CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(3), extra->getCount());
		extra->setCount(0);
	}
};

template <>
struct BtNodeTraits<BtCompositeNodeTest::MyConditionNode>
{
	static const char* name()
	{
		return "BtCompositeNodeTest::MyConditionNode";
	}
};

template <>
struct BtNodeTraits<BtCompositeNodeTest::MyActionNode>
{
	static const char* name()
	{
		return "BtCompositeNodeTest::MyActionNode";
	}
};

static BtNodeFactoryRegister<BtCompositeNodeTest::MyConditionNode> gsConditionReg;
static BtNodeFactoryRegister<BtCompositeNodeTest::MyActionNode> gsActionReg;

CPPUNIT_TEST_SUITE_REGISTRATION(BtCompositeNodeTest);
