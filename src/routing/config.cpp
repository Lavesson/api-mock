#include "config.h"
#include "routeregistry.h"
#include "routingtemplate.h"

#include "controllers/dashboardcontroller.h"

void ApiMock::ConfigureRoutes(RouteRegistry* routes) {
	routes->registerRoute(RoutingTemplate("/dashboard"), new DashboardController);
}