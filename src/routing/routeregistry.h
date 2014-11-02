#ifndef	APIMOCK_ROUTEREGISTRY_H
#define APIMOCK_ROUTEREGISTRY_H

namespace ApiMock {
	class Controller;
	class RoutingTemplate;

	class RouteRegistry {
	public:
		virtual ~RouteRegistry() {}
		virtual void registerRoute(RoutingTemplate route, Controller* ctrl) = 0;
	};
}

#endif