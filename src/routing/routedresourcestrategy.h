#ifndef	APIMOCK_ROUTEDRESOURCESTRATEGY_H
#define APIMOCK_ROUTEDRESOURCESTRATEGY_H

#include "http/resourcestrategy.h"

namespace ApiMock {
	class RoutedResourceStrategy : public ResourceStrategy {
	public:
		ResponseData CreateResponse(RequestData const& request) override;
	};
}

#endif