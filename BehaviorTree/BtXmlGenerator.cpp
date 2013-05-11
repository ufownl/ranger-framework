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

#include "BtXmlGenerator.h"
#include "BtSelectorNode.h"
#include "BtSequenceNode.h"
#include "BtParallelSucceedOnAllNode.h"
#include "BtParallelFailOnAllNode.h"
#include "BtParallelHybridNode.h"
#include "BtDecoratorNotNode.h"
#include "BtDecoratorTimerNode.h"
#include "BtDecoratorCounterNode.h"
#include "BtDecoratorForNode.h"
#include "BtDecoratorUntilNode.h"
#include "BtBehaviorNode.h"
#include <rapidxml/rapidxml_utils.hpp>
#include <string.h>

BtNode* BtXmlGenerator::generate(const char* path)
{
	rapidxml::file<> f(path);
	rapidxml::xml_document<> d;

	d.parse<0>(f.data());

	rapidxml::xml_node<>* xn = d.first_node("BtRoot");
	
	if (!xn)
	{
		return 0;
	}

	rapidxml::xml_attribute<>* xa = xn->first_attribute("class");

	if (!xa)
	{
		return 0;
	}

	BtNode* node = BtNodeFactoryHolder::instance().create(xa->value());

	if (node)
	{
		BtXmlGenerator gen(xn);
		node->accept(gen);
	}

	return node;
}

BtXmlGenerator::BtXmlGenerator(rapidxml::xml_node<>* xml)
	: mXml(xml)
{
}

void BtXmlGenerator::onVisit(BtSelectorNode& node)
{
	generateChildren(node);
}

void BtXmlGenerator::onVisit(BtSequenceNode& node)
{
	generateChildren(node);
}

void BtXmlGenerator::onVisit(BtParallelSucceedOnAllNode& node)
{
	generateChildren(node);
}

void BtXmlGenerator::onVisit(BtParallelFailOnAllNode& node)
{
	generateChildren(node);
}

void BtXmlGenerator::onVisit(BtParallelHybridNode& node)
{
	rapidxml::xml_attribute<>* xa = mXml->first_attribute("count");

	if (xa)
	{
		node.setCount(atoi(xa->value()));
	}

	xa = mXml->first_attribute("result");

	if (xa)
	{
		if (strcmp(xa->value(), "true") == 0)
		{
			node.setResult(true);
		}
		else
		{
			node.setResult(false);
		}
	}

	generateChildren(node);
}

void BtXmlGenerator::onVisit(BtDecoratorNotNode& node)
{
	generateChild(node);
}

void BtXmlGenerator::onVisit(BtDecoratorTimerNode& node)
{
	rapidxml::xml_attribute<>* xa = mXml->first_attribute("cooldown");

	if (xa)
	{
		node.setCooldown(atof(xa->value()));
	}

	xa = mXml->first_attribute("index");

	if (xa)
	{
		node.setIndex(atoi(xa->value()));
	}

	generateChild(node);
}

void BtXmlGenerator::onVisit(BtDecoratorCounterNode& node)
{
	rapidxml::xml_attribute<>* xa = mXml->first_attribute("count");

	if (xa)
	{
		node.setCount(atoi(xa->value()));
	}

	xa = mXml->first_attribute("index");

	if (xa)
	{
		node.setIndex(atoi(xa->value()));
	}

	generateChild(node);
}

void BtXmlGenerator::onVisit(BtDecoratorForNode& node)
{
	rapidxml::xml_attribute<>* xa = mXml->first_attribute("count");

	if (xa)
	{
		node.setCount(atoi(xa->value()));
	}

	generateChild(node);
}

void BtXmlGenerator::onVisit(BtDecoratorUntilNode& node)
{
	rapidxml::xml_attribute<>* xa = mXml->first_attribute("result");

	if (xa)
	{
		if (strcmp(xa->value(), "true") == 0)
		{
			node.setResult(true);
		}
		else
		{
			node.setResult(false);
		}
	}

	xa = mXml->first_attribute("count");

	if (xa)
	{
		node.setCount(atoi(xa->value()));
	}

	generateChild(node);
}

void BtXmlGenerator::onVisit(BtBehaviorNode& node)
{
	rapidxml::xml_attribute<>* xa = mXml->first_attribute("script");

	if (xa)
	{
		node.setScript(xa->value());
	}

	for (rapidxml::xml_node<>* xn = mXml->first_node("BtParam"); xn; xn = xn->next_sibling())
	{
		rapidxml::xml_attribute<>* xan = xn->first_attribute("name");
		rapidxml::xml_attribute<>* xav = xn->first_attribute("value");

		if (xan && xav)
		{
			node.addParam(xan->value(), atof(xav->value()));
		}
	}
}

void BtXmlGenerator::generateChildren(BtNode& node)
{
	for (rapidxml::xml_node<>* xn = mXml->first_node("BtNode"); xn; xn = xn->next_sibling("BtNode"))
	{
		rapidxml::xml_attribute<>* xa = xn->first_attribute("class");

		if (!xa)
		{
			continue;
		}

		BtNode* child = BtNodeFactoryHolder::instance().create(xa->value());

		if (child)
		{
			node.attachChild(child);
			BtXmlGenerator gen(xn);
			child->accept(gen);
		}
	}
}

void BtXmlGenerator::generateChild(BtNode& node)
{
	rapidxml::xml_node<>* xn = mXml->first_node("BtNode");

	if (!xn)
	{
		return;
	}

	rapidxml::xml_attribute<>* xa = xn->first_attribute("class");

	if (!xa)
	{
		return;
	}

	BtNode* child = BtNodeFactoryHolder::instance().create(xa->value());

	if (child)
	{
		node.attachChild(child);
		BtXmlGenerator gen(xn);
		child->accept(gen);
	}
}
