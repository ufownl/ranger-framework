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

#ifndef __Network_NwConnection_H__
#define __Network_NwConnection_H__

#include "Memory/STLAllocator.h"
#include "NwMessageFilter.h"
#include <string>

struct bufferevent;
struct ev_token_bucket_cfg;
class NwEventHandler;
class NwBufferBase;

#if (defined(_WIN32) || defined(_WIN64)) && defined(USE_TCMALLOC)
#include "Memory/TCMallocAllocator.h"
#define NwConnection_Alloc	TCMallocAllocator
#else
#define NwConnection_Alloc	Allocator
#endif  // (_WIN32 || _WIN64) && USE_TCMALLOC

class NwConnection : public RefObject<NwConnection_Alloc, boost::detail::atomic_count>
{
public:
	struct Backend
	{
		bufferevent* backend;
		bufferevent* frontend;
		ev_token_bucket_cfg* rate;
	};

public:
	bool write(const void* data, size_t len);
	bool write(NwBufferBase* buf);

	bool setRateLimit(size_t rr, size_t rb, size_t wr, size_t wb);
	bool setRateLimit(size_t rr, size_t rb, size_t wr, size_t wb, float sec);

	size_t getReadLimit() const;
	size_t getWriteLimit() const;

	const char* getPeerIP() const;
	int getPeerPort() const;

	void setExtraData(void* extra);
	void* getExtraData() const;

	// Internal functions
	NwConnection(NwMessageFilter* filter, NwEventHandler* handler);
	virtual ~NwConnection();

	bool initialize(bufferevent* bev);
	
	const Backend* backend() const;
	NwMessageFilter* filter() const;
	NwEventHandler* handler() const;

private:
	Backend mBackend;

	NwMessageFilterPtr mFilter;
	NwEventHandler* mHandler;

	std::basic_string<
		char,
		std::char_traits<char>,
		STLAllocator<char, NwConnection_Alloc>
	> mIP;
	int mPort;

	void* mExtra;
};

DeclareSmartPointer(NwConnection);

#endif  // __Network_NwConnection_H__
