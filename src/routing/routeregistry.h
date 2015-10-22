#pragma once

#include "routingtemplate.h"

namespace ApiMock {
	class Controller;
	class RoutingTemplate;

	class RouteRegistry {
	public:
		virtual ~RouteRegistry() {}
		virtual void registerRoute(RoutingTemplate route, Controller* ctrl) = 0;
	};
}
