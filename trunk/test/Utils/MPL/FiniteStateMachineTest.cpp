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
#include <boost/mpl/vector.hpp>
#include "MPL/finite_state_machine.h"

class player : public finite_state_machine<player>
{
public:
	struct play { int value; };
	struct pause { int value; };
	struct stop { int value; };
	struct open_close { int value; };

	enum
	{
		close_state,
		stop_state,
		pause_state,
		playing_state,
		initial_state = close_state
	};
	
private:
	void open_player(open_close& e)
	{
		e.value = 0;
	}

	void close_player(open_close& e)
	{
		e.value = 1;
	}

	void start_play(play& e)
	{
		e.value = 2;
	}

	void resume_play(play& e)
	{
		e.value = 3;
	}

	void pause_play(pause& e)
	{
		e.value = 4;
	}

	void stop_play(stop& e)
	{
		e.value = 5;
	}

	TRANSITION_TABLE_BEGIN(player, boost::mpl::vector)
		//    Current		  Event			  Next			  Action
		//  +---------------+---------------+---------------+-----------------------+
		row < close_state	, open_close	, stop_state	, &player::open_player	>,
		//  +---------------+---------------+---------------+-----------------------+
		row < stop_state	, open_close	, close_state	, &player::close_player	>,
		row < stop_state	, play			, playing_state	, &player::start_play	>,
		//  +---------------+---------------+---------------+-----------------------+
		row < playing_state	, open_close	, close_state	, &player::close_player >,
		row < playing_state	, stop			, stop_state	, &player::stop_play	>,
		row < playing_state	, pause			, pause_state	, &player::pause_play	>,
		//  +---------------+---------------+---------------+-----------------------+
		row < pause_state	, open_close	, close_state	, &player::close_player >,
		row < pause_state	, stop			, stop_state	, &player::stop_play	>,
		row < pause_state	, play			, playing_state	, &player::resume_play	>
		//  +---------------+---------------+---------------+-----------------------+
	TRANSITION_TABLE_END
};

class FiniteStateMachineTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(FiniteStateMachineTest);
	CPPUNIT_TEST(test);
	CPPUNIT_TEST_SUITE_END();

public:
	virtual void setUp()
	{
	}

	virtual void tearDown()
	{
	}

private:
	void test()
	{
		player p;

		CPPUNIT_ASSERT_EQUAL(static_cast<int>(player::initial_state), p.current_state());
		CPPUNIT_ASSERT_EQUAL(static_cast<int>(player::stop_state), p.process_event(open_close));
		CPPUNIT_ASSERT_EQUAL(0, open_close.value);
		CPPUNIT_ASSERT_EQUAL(static_cast<int>(player::playing_state), p.process_event(play));
		CPPUNIT_ASSERT_EQUAL(2, play.value);
		CPPUNIT_ASSERT_EQUAL(static_cast<int>(player::pause_state), p.process_event(pause));
		CPPUNIT_ASSERT_EQUAL(4, pause.value);
		CPPUNIT_ASSERT_EQUAL(static_cast<int>(player::playing_state), p.process_event(play));
		CPPUNIT_ASSERT_EQUAL(3, play.value);
		CPPUNIT_ASSERT_EQUAL(static_cast<int>(player::stop_state), p.process_event(stop));
		CPPUNIT_ASSERT_EQUAL(5, stop.value);
		CPPUNIT_ASSERT_EQUAL(static_cast<int>(player::close_state), p.process_event(open_close));
		CPPUNIT_ASSERT_EQUAL(1, open_close.value);
	}

	player::open_close open_close;
	player::play play;
	player::pause pause;
	player::stop stop;
};

CPPUNIT_TEST_SUITE_REGISTRATION(FiniteStateMachineTest);
