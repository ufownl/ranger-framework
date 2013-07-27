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
#include "ArMeshData.h"

static void* dtAllocCustom(int size, dtAllocHint)
{
#ifdef _DEBUG
	return ArMeshData_Alloc::allocate(size, __FILE__, __LINE__);
#else
	return ArMeshData_Alloc::allocate(size);
#endif  // _DEBUG
}

static void dtFreeCustom(void* p)
{
	ArMeshData_Alloc::deallocate(p);
}

class ArMeshDataTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ArMeshDataTest);
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
		dtNavMeshParams params = {0};

		params.maxTiles = 3;

		ArMeshDataPtr data = RfNew ArMeshData(params);
		ArMeshTilePtr tiles[5];

		for (int i = 0; i < 5; ++i)
		{
			tiles[i] = RfNew ArMeshTile(static_cast<unsigned char*>(dtAlloc(1024, DT_ALLOC_PERM)), 1024);

			if (i < 3)
			{
				CPPUNIT_ASSERT(data->addTile(tiles[i]));
			}
			else
			{
				CPPUNIT_ASSERT(!data->addTile(tiles[i]));
			}
		}

		CPPUNIT_ASSERT_EQUAL(params.maxTiles, data->getCount());

		for (int i = 0; i < data->getCount(); ++i)
		{
			CPPUNIT_ASSERT_EQUAL(tiles[i].data(), data->getTile(i));
			CPPUNIT_ASSERT_EQUAL(static_cast<long>(2), tiles[i]->getRefCount());
		}

		data->removeTile(4);
		data->removeTile(3);

		for (int i = 0; i < data->getCount(); ++i)
		{
			CPPUNIT_ASSERT_EQUAL(tiles[i].data(), data->getTile(i));
			CPPUNIT_ASSERT_EQUAL(static_cast<long>(2), tiles[i]->getRefCount());
		}

		data->removeTile(0);

		CPPUNIT_ASSERT_EQUAL(static_cast<long>(1), tiles[0]->getRefCount());
		CPPUNIT_ASSERT_EQUAL(static_cast<long>(2), tiles[1]->getRefCount());
		CPPUNIT_ASSERT_EQUAL(static_cast<long>(2), tiles[2]->getRefCount());
		CPPUNIT_ASSERT_EQUAL(tiles[2].data(), data->getTile(0));
		CPPUNIT_ASSERT_EQUAL(tiles[1].data(), data->getTile(1));

		data->removeTile(1);

		CPPUNIT_ASSERT_EQUAL(static_cast<long>(1), tiles[0]->getRefCount());
		CPPUNIT_ASSERT_EQUAL(static_cast<long>(1), tiles[1]->getRefCount());
		CPPUNIT_ASSERT_EQUAL(static_cast<long>(2), tiles[2]->getRefCount());
		CPPUNIT_ASSERT_EQUAL(tiles[2].data(), data->getTile(0));
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(ArMeshDataTest);
