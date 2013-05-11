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

#ifndef __Utils_MPL_event_dispatcher_H__
#define __Utils_MPL_event_dispatcher_H__

template <class _row, class _left, class _right>
struct event_dispatcher
{
	typedef typename _row::fsm_t fsm_t;
	typedef typename _row::event event;
	typedef event_dispatcher type;

	static int dispatch(fsm_t &fsm, int state, event &e)
	{
		if (state == _row::current_state)
		{
			_row::execute(fsm, e);
			return _row::next_state;
		}
		else if (state < _row::current_state)
		{
			return _left::type::dispatch(fsm, state, e);
		}
		else
		{
			return _right::type::dispatch(fsm, state, e);
		}
	}
};

struct default_event_dispatch
{
	typedef default_event_dispatch type;

	template <class _fsm, class _event>
	static int dispatch(finite_state_machine<_fsm> &fsm, int state, _event &e)
	{
		return fsm.call_no_transition(state, e);
	}
};

#endif  // __Utils_MPL_event_dispatcher_H__
