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

#ifndef __Network_NwMessageFilter_H__
#define __Network_NwMessageFilter_H__

#include "Object/RefObject.h"
#include "Object/SmartPointer.h"
#include "Object/AbstractFactory.h"
#include <boost/detail/atomic_count.hpp>
#include <boost/mpl/vector.hpp>

class NwBufferBase;

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define NwMessageFilter_Alloc	TCMallocAllocator
#else
#define NwMessageFilter_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class NwMessageFilter : public RefObject<NwMessageFilter_Alloc, boost::detail::atomic_count>
{
public:
	enum result
	{
		eOK,
		eMORE,
		eERROR
	};

	virtual result encode(NwBufferBase* src, NwBufferBase* dst);
	virtual result decode(NwBufferBase* src, NwBufferBase* dst) = 0;
};

DeclareSmartPointer(NwMessageFilter);

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define NwMessageFilterFactory_Alloc	TCMallocAllocator
#else
#define NwMessageFilterFactory_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class NwMessageFilterFactory
	: public AbstractFactory<boost::mpl::vector<NwMessageFilter> >
	, public RefObject<NwMessageFilterFactory_Alloc, boost::detail::atomic_count>
{
public:
	typedef AbstractFactory<boost::mpl::vector<NwMessageFilter> >::ProductSeq ProductSeq;
};

DeclareSmartPointer(NwMessageFilterFactory);

template <class T>
NwMessageFilterFactory* createNwMessageFilterFactory()
{
	return RfNew ConcreteFactory<NwMessageFilterFactory, boost::mpl::vector<T>, OpRfNewCfUnit>;
}

#endif  // __Network_NwMessageFilter_H__
