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

#ifndef __Utils_Multimethods_FastDispatcher_H__
#define __Utils_Multimethods_FastDispatcher_H__

#include <vector>
#include <assert.h>

#define INDEXABLE_DECL()	\
	static int& _class_index_static();	\
	virtual int& _class_index();

#define INDEXABLE_IMPL(classname)	\
	int& classname::_class_index_static()	\
	{	\
		static int idx = -1;	\
		return idx;	\
	}	\
	int& classname::_class_index()	\
	{	\
		assert(typeid(*this) == typeid(classname));	\
		return _class_index_static();	\
	}

template <class _lhs_base, class _rhs_base, class _result, class _callback, class _error_handler>
class FastDispatcher
{
private:
	struct CallbackNode
	{
		CallbackNode()
			: regist(false)
		{
		}

		_callback callback;
		bool regist;
	};

	typedef std::vector<CallbackNode> row_t;
	typedef std::vector<row_t> matrix_t;

public:
	template <class _lhs, class _rhs>
	void regist(const _callback& fn)
	{
		int& lhs = _lhs::_class_index_static();

		if (lhs < 0)
		{
			lhs = _generate_index();
		}

		if (mCallbacks.size() <= static_cast<size_t>(lhs))
		{
			mCallbacks.resize(lhs + 1);
		}

		row_t& row = mCallbacks[lhs];
		int& rhs = _rhs::_class_index_static();

		if (rhs < 0)
		{
			rhs = _generate_index();
		}

		if (row.size() <= static_cast<size_t>(rhs))
		{
			row.resize(rhs + 1);
		}

		row[rhs].callback = fn;
		row[rhs].regist = true;
	}

	_result dispatch(_lhs_base& lhs, _rhs_base& rhs)
	{
		int li = lhs._class_index();
		int ri = rhs._class_index();

		if (li < 0 || ri < 0 ||
			static_cast<size_t>(li) >= mCallbacks.size() ||
			static_cast<size_t>(ri) >= mCallbacks[li].size() ||
			!mCallbacks[li][ri].regist)
		{
			return _error_handler::onError(lhs, rhs);
		}

		return mCallbacks[li][ri].callback(lhs, rhs);
	}

private:
	static int _generate_index()
	{
		static int idx = 0;
		return idx++;
	}

private:
	matrix_t mCallbacks;
};

#endif  // __Utils_Multimethods_FastDispatcher_H__
