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

#ifndef __BehaviorTree_BtXmlGenerator_H__
#define __BehaviorTree_BtXmlGenerator_H__

#include "BtNode.h"
#include <rapidxml/rapidxml.hpp>

class BtXmlGenerator : protected BtGenerator
{
public:
	static BtNode* generate(const char* path);

protected:
	BtXmlGenerator(rapidxml::xml_node<>* xml);

	virtual void onVisit(BtSelectorNode& node);
	virtual void onVisit(BtSequenceNode& node);
	virtual void onVisit(BtParallelSucceedOnAllNode& node);
	virtual void onVisit(BtParallelFailOnAllNode& node);
	virtual void onVisit(BtParallelHybridNode& node);
	virtual void onVisit(BtDecoratorNotNode& node);
	virtual void onVisit(BtDecoratorTimerNode& node);
	virtual void onVisit(BtDecoratorCounterNode& node);
	virtual void onVisit(BtDecoratorForNode& node);
	virtual void onVisit(BtDecoratorUntilNode& node);
	virtual void onVisit(BtBehaviorNode& node);

private:
	void generateChildren(BtNode& node);
	void generateChild(BtNode& node);

private:
	rapidxml::xml_node<>* mXml;
};

#endif  // __BehaviorTree_BtXmlGenerator_H__
