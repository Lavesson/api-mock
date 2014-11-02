#ifndef	APIMOCK_ROUTEDRESOURCESTRATEGY_H
#define APIMOCK_ROUTEDRESOURCESTRATEGY_H

#include "http/resourcestrategy.h"

namespace ApiMock {
	class RoutedResourceStrategy : public ResourceStrategy {
	public:
		ResponseData createResponse(RequestData const& request) override;
	};
}

#endif