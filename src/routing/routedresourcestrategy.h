#ifndef	APIMOCK_ROUTEDRESOURCESTRATEGY_H
#define APIMOCK_ROUTEDRESOURCESTRATEGY_H

#include "http/resourcestrategy.h"
#include "routeregistry.h"
#include "routingtemplate.h"
#include <unordered_map>

namespace ApiMock {
	class Controller;
	enum HTTP_RESPONSE_CODE;

	class RoutedResourceStrategy : 
		public ResourceStrategy, public RouteRegistry {
		std::unordered_map<RoutingTemplate, Controller*> _routeMap;
		ResponseData errorResponse(HTTP_RESPONSE_CODE status);
		Controller* matchRoute(const std::string& uri);

	public:
		void registerRoute(RoutingTemplate route, Controller* ctrl) override;
		ResponseData createResponse(RequestData const& request) override;
	};
}

#endif