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

#ifndef __BehaviorTree_BtNode_H__
#define __BehaviorTree_BtNode_H__

#include "Object/RefObject.h"
#include "Object/SmartPointer.h"
#include "Object/Visitor.h"
#include "Object/Factory.h"
#include <boost/mpl/vector.hpp>

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define BtNode_Alloc	TCMallocAllocator
#else
#define BtNode_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class BtParams;

// Composite Node
class BtSelectorNode;
class BtSequenceNode;
class BtParallelSucceedOnAllNode;
class BtParallelFailOnAllNode;
class BtParallelHybridNode;

// Decorator Node
class BtDecoratorNotNode;
class BtDecoratorTimerNode;
class BtDecoratorCounterNode;
class BtDecoratorForNode;
class BtDecoratorUntilNode;

// Condition&Action Node
class BtBehaviorNode;

typedef Visitor<
	boost::mpl::vector<
		BtSelectorNode,
		BtSequenceNode,
		BtParallelSucceedOnAllNode,
		BtParallelFailOnAllNode,
		BtParallelHybridNode,
		BtDecoratorNotNode,
		BtDecoratorTimerNode,
		BtDecoratorCounterNode,
		BtDecoratorForNode,
		BtDecoratorUntilNode,
		BtBehaviorNode
	>
> BtGenerator;

class BtNode : public RefObject<BtNode_Alloc>
{
public:
	VISITABLE_DECL_ABS(BtGenerator);

public:
	BtNode();
	virtual ~BtNode();

	virtual bool execute(BtParams* params) = 0;

	void attachChild(BtNode* node);
	BtNode* getFirstChild();
	BtNode* getNextSibling();

private:
	SmartPointer<BtNode> mNextSibling;
	SmartPointer<BtNode> mFirstChild;
	BtNode* mLastChild;
};

DeclareSmartPointer(BtNode);

template <class T>
struct BtNodeTraits;

template <>
struct BtNodeTraits<BtNode>
{
	static const char* name()
	{
		return "BtNode";
	}
};

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define BtNodeFactory_Alloc	TCMallocAllocator
#else
#define BtNodeFactory_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

struct BtNodeFactory
	: public MemObject<BtNodeFactory_Alloc>
	, public Factory<
		BtNode,
		std::string,
		BtNode* (*)(),
		SingleThread
	> 
{
};

typedef SingletonHolder<
	BtNodeFactory,
	SingletonOpRfNewCreation,
	SingletonDestroyAtExit
> BtNodeFactoryHolder;

template <class T>
class BtNodeFactoryRegister
{
public:
	BtNodeFactoryRegister()
	{
		BtNodeFactoryHolder::instance().regist(BtNodeTraits<T>::name(), &BtNodeFactoryRegister::create);
	}

private:
	static BtNode* create()
	{
		return RfNew T;
	}
};

#endif  // __BehaviorTree_BtNode_H__
