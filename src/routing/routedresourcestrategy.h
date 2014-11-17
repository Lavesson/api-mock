#ifndef	APIMOCK_ROUTEDRESOURCESTRATEGY_H
#define APIMOCK_ROUTEDRESOURCESTRATEGY_H

#include "http/resourcestrategy.h"
#include "routeregistry.h"
#include "routingtemplate.h"
#include "controllers/controller.h"
#include <vector>
#include <memory>

namespace ApiMock {
	enum HTTP_RESPONSE_CODE;

	class RoutedResourceStrategy : 
		public ResourceStrategy, public RouteRegistry {
		std::vector<std::pair<RoutingTemplate, std::unique_ptr<Controller>>> _routeMap;
		ResponseData errorResponse(HTTP_RESPONSE_CODE status);
		Controller* matchRoute(RequestData* request);

	public:
		void registerRoute(RoutingTemplate route, Controller* ctrl) override;
		ResponseData createResponse(RequestData const& request) override;
	};
}

#endif
