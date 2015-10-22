#pragma once
#include "requestdata.h"
#include "responsedata.h"

namespace ApiMock {
	class ResourceStrategy {
	public:
		virtual ~ResourceStrategy() {}
		virtual ResponseData createResponse(const RequestData& request) = 0;
	};
}
