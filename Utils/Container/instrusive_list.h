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

#ifndef __Utils_Container_instrusive_list_H__
#define __Utils_Container_instrusive_list_H__

#include <iterator>
#include <limits>
#include <stddef.h>

template <class T>
class instrusive_list_node
{
public:
	typedef T* link_type;

public:
	link_type& next()
	{
		return mNext;
	}

	link_type& prev()
	{
		return mPrev;
	}

	const link_type& next() const
	{
		return mNext;
	}

	const link_type& prev() const
	{
		return mPrev;
	}

private:
	link_type mNext;
	link_type mPrev;
};

template <class _node, class _ptr = _node*, class _ref = _node&>
struct instrusive_list_iterator : std::iterator<std::bidirectional_iterator_tag, _node, ptrdiff_t, _ptr, _ref>
{
	typedef _ptr link_type;
	typedef instrusive_list_iterator<_node> iterator;
	typedef instrusive_list_iterator<_node, _ptr, _ref> self;

	instrusive_list_iterator()
	{
	}

	instrusive_list_iterator(link_type node)
		: mNode(node)
	{
	}

	instrusive_list_iterator(const iterator& rhs)
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

	self& operator -- ()
	{
		mNode = mNode->prev();
		return *this;
	}

	self operator -- (int)
	{
		self res = *this;

		mNode = mNode->prev();
		return res;
	}

	link_type mNode;
};

template <class _node>
class instrusive_list
{
public:
	typedef _node value_type;
	typedef _node* pointer;
	typedef _node* const_pointer;
	typedef _node& reference;
	typedef _node& const_reference;

	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	typedef instrusive_list_iterator<_node> iterator;
	typedef instrusive_list_iterator<_node, const _node*, const _node&> const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef typename iterator::link_type link_type;

public:
	instrusive_list()
	{
		mHead.next() = &mHead;
		mHead.prev() = &mHead;
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

	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	}

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(begin());
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

	reference back()
	{
		return *(--end());
	}

	const_reference front() const
	{
		return *begin();
	}

	const_reference back() const
	{
		return *(--end());
	}

	static iterator insert(iterator pos, reference node)
	{
		node.next() = pos.mNode;
		node.prev() = pos.mNode->prev();
		pos.mNode->prev()->next() = &node;
		pos.mNode->prev() = &node;
		return &node;
	}

	void push_front(reference node)
	{
		insert(begin(), node);
	}

	void push_back(reference node)
	{
		insert(end(), node);
	}

	static iterator erase(iterator pos)
	{
		link_type nextNode = pos.mNode->next();
		link_type prevNode = pos.mNode->prev();

		prevNode->next() = nextNode;
		nextNode->prev() = prevNode;
		return nextNode;
	}

	static iterator erase(iterator first, iterator last)
	{
		link_type nextNode = last.mNode;
		link_type prevNode = first.mNode->prev();

		prevNode->next() = nextNode;
		nextNode->prev() = prevNode;
		return nextNode;
	}

	void pop_front()
	{
		erase(begin());
	}

	void pop_back()
	{
		erase(--end());
	}

	void clear()
	{
		erase(begin(), end());
	}

	void remove(reference node)
	{
		link_type nextNode = node.next();
		link_type prevNode = node.prev();

		prevNode->next() = nextNode;
		nextNode->prev() = prevNode;
	}

	template <class _unary_predicate>
	void remove_if(_unary_predicate pred)
	{
		for (iterator i = begin(); i != end(); )
		{
			iterator t = i;

			++t;
			if (pred(*i))
			{
				erase(i);
			}
			i = t;
		}
	}

protected:
	_node mHead;
};

#endif  // __Utils_Container_instrusive_list_H__
