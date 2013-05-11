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

#include "MPL/finite_state_machine.h"
#include <boost/mpl/vector.hpp>
#include <stdio.h>

class player : public finite_state_machine<player>
{
public:
	struct play {};
	struct pause {};
	struct stop {};
	struct open_close {};
	
private:
	void open_player(open_close&)
	{
		puts(__FUNCTION__);
	}

	void close_player(open_close&)
	{
		puts(__FUNCTION__);
	}

	void start_play(play&)
	{
		puts(__FUNCTION__);
	}

	void resume_play(play&)
	{
		puts(__FUNCTION__);
	}

	void pause_play(pause&)
	{
		puts(__FUNCTION__);
	}

	void stop_play(stop&)
	{
		puts(__FUNCTION__);
	}

	enum
	{
		close_state,
		stop_state,
		pause_state,
		playing_state,
		initial_state = close_state
	};

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

int main()
{
	player p;

	player::open_close open_close;
	player::play play;
	player::pause pause;
	player::stop stop;

	p.process_event(open_close);
	p.process_event(play);
	p.process_event(pause);
	p.process_event(play);
	p.process_event(stop);
	p.process_event(open_close);

	return 0;
}
