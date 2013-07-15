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

#include <event2/buffer.h>
#include "NwBufferBase.h"
#include <stdexcept>

bool NwBufferBase::append(const void* data, size_t len)
{
	return evbuffer_add(mBackend, data, len) == 0;
}

bool NwBufferBase::append(NwBufferBase* buf)
{
	return evbuffer_add_buffer(mBackend, buf->mBackend) == 0;
}

int NwBufferBase::printf(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	int ret = evbuffer_add_vprintf(mBackend, fmt, ap);
	va_end(ap);

	return ret;
}

int NwBufferBase::vprintf(const char* fmt, va_list ap)
{
	return evbuffer_add_vprintf(mBackend, fmt, ap);
}

int NwBufferBase::remove(void* data, size_t len)
{
	return evbuffer_remove(mBackend, data, len);
}

int NwBufferBase::remove(NwBufferBase* buf, size_t len)
{
	return evbuffer_remove_buffer(mBackend, buf->mBackend, len);
}

int NwBufferBase::copyout(void* data, size_t len) const
{
	return evbuffer_copyout(mBackend, data, len);
}

bool NwBufferBase::drain(size_t len)
{
	return evbuffer_drain(mBackend, len) == 0;
}

char* NwBufferBase::readln(size_t* len /* = 0 */, eol_style style /* = EOL_CRLF */)
{
	switch (style)
	{
	case EOL_ANY:
		return evbuffer_readln(mBackend, len, EVBUFFER_EOL_ANY);
	case EOL_CRLF:
		return evbuffer_readln(mBackend, len, EVBUFFER_EOL_CRLF);
	case EOL_CRLF_STRICT:
		return evbuffer_readln(mBackend, len, EVBUFFER_EOL_CRLF_STRICT);
	case EOL_LF:
		return evbuffer_readln(mBackend, len, EVBUFFER_EOL_LF);
	default:
		return 0;
	}
}

void NwBufferBase::free(char* line)
{
	if (line)
	{
		NwBufferBase_Alloc::deallocate(line);
	}
}

int NwBufferBase::search(void* src, size_t len, int pos) const
{
	evbuffer_ptr ptr;

	evbuffer_ptr_set(mBackend, &ptr, pos, EVBUFFER_PTR_SET);
	ptr = evbuffer_search(mBackend, (const char*)src, len, &ptr);

	return ptr.pos;
}

size_t NwBufferBase::size() const
{
	return evbuffer_get_length(mBackend);
}

NwBufferBase::NwBufferBase(evbuffer* evbuf)
	: mBackend(evbuf)
{
	if (!evbuf)
	{
		throw std::invalid_argument("Invalid evbuf.");
	}
}

NwBufferBase::~NwBufferBase()
{
}

evbuffer* NwBufferBase::backend() const
{
	return mBackend;
}
