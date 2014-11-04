#include "config.h"
#include "routeregistry.h"
#include "routingtemplate.h"
#include "ioc/ioc.h"
#include "controllers/dashboardcontroller.h"
#include "infrastructure/filecontentservice.h"


void ApiMock::ConfigureDependencies() {
	ServiceRegistry::Register<ContentService>(new FileContentService);
}

void ApiMock::ConfigureRoutes(RouteRegistry* routes) {
	routes->registerRoute(RoutingTemplate("/dashboard"), new DashboardController);
}