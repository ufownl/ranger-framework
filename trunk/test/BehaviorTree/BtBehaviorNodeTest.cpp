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
#include "BtConditionNode.h"
#include "BtActionNode.h"
#include "BtParams.h"
#include "BtXmlGenerator.h"

class BtBehaviorNodeTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(BtBehaviorNodeTest);
	CPPUNIT_TEST(test);
	CPPUNIT_TEST_SUITE_END();

public:
	class MyConditionNode : public BtConditionNode
	{
	protected:
		virtual void defineExtraData() {}
		virtual void exportExtraData(void* extra) {}
	};

	class MyActionNode : public BtActionNode
	{
	protected:
		virtual void defineExtraData() {}
		virtual void exportExtraData(void* extra) {}
	};

public:
	virtual void setUp()
	{
		BtXmlGenerator::regist<
			boost::mpl::vector<
				MyConditionNode,
				MyActionNode
			>
		>();
	}

	virtual void tearDown()
	{
	}

private:
	void test()
	{
		BtParamsPtr params = RfNew BtParams(32);
		
		BtNodePtr root = BtXmlGenerator::generate("./BehaviorTree/bt_cond_true.xml");
		CPPUNIT_ASSERT(root);
		CPPUNIT_ASSERT(root->execute(params));

		root = BtXmlGenerator::generate("./BehaviorTree/bt_cond_false.xml");
		CPPUNIT_ASSERT(root);
		CPPUNIT_ASSERT(!root->execute(params));

		root = BtXmlGenerator::generate("./BehaviorTree/bt_act_true.xml");
		CPPUNIT_ASSERT(root);
		CPPUNIT_ASSERT(root->execute(params));

		root = BtXmlGenerator::generate("./BehaviorTree/bt_act_false.xml");
		CPPUNIT_ASSERT(root);
		CPPUNIT_ASSERT(!root->execute(params));
	}
};

template <>
struct BtNodeTraits<BtBehaviorNodeTest::MyConditionNode>
{
	static const char* name()
	{
		return "BtBehaviorNodeTest::MyConditionNode";
	}
};

template <>
struct BtNodeTraits<BtBehaviorNodeTest::MyActionNode>
{
	static const char* name()
	{
		return "BtBehaviorNodeTest::MyActionNode";
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(BtBehaviorNodeTest);
