#ifndef	APIMOCK_RESOURCESTRATEGY_H
#define APIMOCK_RESOURCESTRATEGY_H

#include "requestdata.h"
#include "responsedata.h"

namespace ApiMock {
	class ResourceStrategy {
	public:
		virtual ~ResourceStrategy() {}
		virtual ResponseData CreateResponse(const RequestData& request) = 0;
	};
}

#endif