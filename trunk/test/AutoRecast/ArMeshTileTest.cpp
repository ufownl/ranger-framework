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
#include "ArMeshTile.h"

static void* dtAllocCustom(int size, dtAllocHint)
{
#ifdef _DEBUG
	return ArMeshTile_Alloc::allocate(size, __FILE__, __LINE__);
#else
	return ArMeshTile_Alloc::allocate(size);
#endif  // _DEBUG
}

static void dtFreeCustom(void* p)
{
	ArMeshTile_Alloc::deallocate(p);
}

class ArMeshTileTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ArMeshTileTest);
	CPPUNIT_TEST(test);
	CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp()
	{
		dtAllocSetCustom(dtAllocCustom, dtFreeCustom);
	}

	virtual void tearDown()
	{
		dtAllocSetCustom(0, 0);
	}

private:
	void test()
	{
		int size = 1024;
		unsigned char* data = static_cast<unsigned char*>(dtAlloc(size, DT_ALLOC_PERM));
		dtTileRef ref = 64;

		CPPUNIT_ASSERT(data);

		ArMeshTilePtr tile = RfNew ArMeshTile(data, size, ref);

		CPPUNIT_ASSERT_EQUAL(data, tile->getData());
		CPPUNIT_ASSERT_EQUAL(size, tile->getSize());
		CPPUNIT_ASSERT_EQUAL(ref, tile->getRef());
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(ArMeshTileTest);
