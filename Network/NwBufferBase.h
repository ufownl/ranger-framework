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

#ifndef __Network_NwBufferBase_H__
#define __Network_NwBufferBase_H__

#include "Object/RefObject.h"
#include "Object/SmartPointer.h"
#include <boost/detail/atomic_count.hpp>
#include <stdarg.h>

struct evbuffer;

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define NwBufferBase_Alloc	TCMallocAllocator
#else
#define NwBufferBase_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class NwBufferBase : public RefObject<NwBufferBase_Alloc, boost::detail::atomic_count>
{
public:
	bool append(const void* data, size_t len);
	bool append(NwBufferBase* buf);
	int printf(const char* fmt, ...);
	int vprintf(const char* fmt, va_list ap);

	int remove(void* data, size_t len);
	int remove(NwBufferBase* buf, size_t len);
	int copyout(void* data, size_t len) const;
	bool drain(size_t len);
	
	enum eol_style
	{
		EOL_ANY,
		EOL_CRLF,
		EOL_CRLF_STRICT,
		EOL_LF
	};
	
	char* readln(size_t* len = 0, eol_style style = EOL_CRLF);
	static void free(char* line);

	int search(void* src, size_t len, int pos = 0) const;
	size_t size() const;

	// Internal functions
	NwBufferBase(evbuffer* evbuf);
	virtual ~NwBufferBase();

	evbuffer* backend() const;

private:
	evbuffer* const mBackend;
};

DeclareSmartPointer(NwBufferBase);

#endif  // __Network_NwBufferBase_H__
