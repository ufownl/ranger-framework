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

#ifndef __Utils_MPL_finite_state_machine_H__
#define __Utils_MPL_finite_state_machine_H__

#include "generate_dispatcher.h"

#include <assert.h>

template <class T>
class finite_state_machine
{
public:
	template <class _event>
	int process_event(_event &e)
	{
		typedef typename generate_dispatcher<typename T::transition_table, _event>::type dispatcher;

		m_state = dispatcher::dispatch(*static_cast<T*>(this), m_state, e);
		return m_state;
	}

	int current_state() const
	{
		return m_state;
	}

protected:
	finite_state_machine()
		: m_state(T::initial_state)
	{
	}

	template <int _current_state, class _event, int _next_state, void (T::*_action)(_event&)>
	struct row
	{
		static const int current_state = _current_state;
		static const int next_state = _next_state;
		typedef _event event;
		typedef T fsm_t;

		static void execute(T &fsm, _event &e)
		{
			(fsm.*_action)(e);
		}
	};

	template <class _event>
	int call_no_transition(int state, _event &e)
	{
		return static_cast<T*>(this)->no_transition(state, e);
	}

	template <class _event>
	int no_transition(int state, _event &e)
	{
		assert(!"no transition.");
		return state;
	}

private:
	friend struct default_event_dispatch;

private:
	int m_state;
};

#include "event_dispatcher.h"

#define TRANSITION_TABLE_BEGIN(T, seq)				\
	private:										\
		friend class finite_state_machine<T>;		\
		struct transition_table						\
			: seq<									\

#define TRANSITION_TABLE_END						\
			>										\
		{											\
		};											\

#endif  // __Utils_MPL_finite_state_machine_H__
