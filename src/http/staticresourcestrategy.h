#ifndef	APIMOCK_STATICRESOURCESTRATEGY_H
#define APIMOCK_STATICRESOURCESTRATEGY_H

#include "resourcestrategy.h"

namespace ApiMock {
	class StaticResourceStrategy : public ResourceStrategy {
	public:
		ResponseData createResponse(RequestData const& request) override;
	};
}

#endif