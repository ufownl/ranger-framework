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

#ifndef __Utils_Container_instrusive_slist_H__
#define __Utils_Container_instrusive_slist_H__

#include <iterator>
#include <limits>
#include <stddef.h>

template <class T>
class instrusive_slist_node
{
public:
	typedef T* link_type;

public:
	link_type& next()
	{
		return mNext;
	}

	const link_type& next() const
	{
		return mNext;
	}

private:
	link_type mNext;
};

template <class _node, class _ptr = _node*, class _ref = _node&>
struct instrusive_slist_iterator : std::iterator<std::forward_iterator_tag, _node, ptrdiff_t, _ptr, _ref>
{
	typedef _ptr link_type;
	typedef instrusive_slist_iterator<_node> iterator;
	typedef instrusive_slist_iterator<_node, _ptr, _ref> self;

	instrusive_slist_iterator()
	{
	}

	instrusive_slist_iterator(link_type node)
		: mNode(node)
	{
	}

	instrusive_slist_iterator(const iterator& rhs)
		: mNode(rhs.mNode)
	{
	}

	bool operator == (const self& rhs)
	{
		return mNode == rhs.mNode;
	}

	bool operator != (const self& rhs)
	{
		return mNode != rhs.mNode;
	}

	_ref operator * () const
	{
		return *mNode;
	}

	_ptr operator -> () const
	{
		return mNode;
	}

	self& operator ++ ()
	{
		mNode = mNode->next();
		return *this;
	}

	self operator ++ (int)
	{
		self res = *this;

		mNode = mNode->next();
		return res;
	}

	link_type mNode;
};

template <class _node>
class instrusive_slist
{
public:
	typedef _node value_type;
	typedef _node* pointer;
	typedef _node* const_pointer;
	typedef _node& reference;
	typedef _node& const_reference;

	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	typedef instrusive_slist_iterator<_node> iterator;
	typedef instrusive_slist_iterator<_node, const _node*, const _node&> const_iterator;

	typedef typename iterator::link_type link_type;

public:
	instrusive_slist()
	{
		mHead.next() = &mHead;
	}

	iterator begin()
	{
		return mHead.next();
	}

	iterator end()
	{
		return &mHead;
	}

	const_iterator begin() const
	{
		return mHead.next();
	}

	const_iterator end() const
	{
		return &mHead;
	}

	bool empty() const
	{
		return mHead.next() == &mHead;
	}

	size_type size() const
	{
		return std::distance(begin(), end());
	}

	size_type max_size() const
	{
		return std::numeric_limits<size_type>::max();
	}

	reference front()
	{
		return *begin();
	}

	const_reference front() const
	{
		return *begin();
	}

	void push_front(reference node)
	{
		node.next() = mHead.next();
		mHead.next() = &node;
	}

	void pop_front()
	{
		mHead.next() = mHead.next()->next();
	}

	void clear()
	{
		mHead.next() = &mHead;
	}

	iterator insert(iterator pos, reference node)
	{
		for (pointer p = &mHead; p->next() != &mHead; p = p->next())
		{
			if (p->next() == pos.mNode)
			{
				node.next() = pos.mNode;
				p->next() = &node;
				return &node;
			}
		}
		return &mHead;
	}

	iterator erase(iterator pos)
	{
		for (pointer p = &mHead; p->next() != &mHead; p = p->next())
		{
			if (p->next() == pos.mNode)
			{
				p->next() = pos.mNode->next();
				return p->next();
			}
		}
		return &mHead;
	}

	iterator erase(iterator first, iterator last)
	{
		for (pointer p = &mHead; p->next() != &mHead; p = p->next())
		{
			if (p->next() == first.mNode)
			{
				p->next() = last.mNode;
				return last;
			}
		}
		return &mHead;
	}

	static iterator insert_after(iterator pos, reference node)
	{
		node.next() = pos.mNode->next();
		pos.mNode->next() = &node;
		return &node;
	}

	iterator erase_after(iterator pos)
	{
		if (pos.mNode->next() != &mHead)
		{
			pos.mNode->next() = pos.mNode->next()->next();
		}
		return pos.mNode->next();
	}

	void remove(reference node)
	{
		for (pointer p = &mHead; p->next() != &mHead; p = p->next())
		{
			if (p->next() == &node)
			{
				p->next() = node.next();
				return;
			}
		}
	}

	template <class _unary_predicate>
	void remove_if(_unary_predicate pred)
	{
		for (pointer p = &mHead; p->next() != &mHead; )
		{
			if (pred(*p->next()))
			{
				p->next() = p->next()->next();
			}
			else
			{
				p = p->next();
			}
		}
	}

	void remove_after(reference node)
	{
		if (node.next() != &mHead)
		{
			node.next() = node.next()->next();
		}
	}

protected:
	_node mHead;
};

#endif  // __Utils_Container_instrusive_slist_H__
