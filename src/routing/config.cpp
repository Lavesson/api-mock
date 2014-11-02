#include "config.h"
#include "routeregistry.h"
#include "routingtemplate.h"

void ApiMock::ConfigureRoutes(RouteRegistry* routes) {
	routes->registerRoute(RoutingTemplate("/test/{id}"), nullptr);
}