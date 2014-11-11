#include "config.h"
#include "routeregistry.h"
#include "routingtemplate.h"
#include "ioc/ioc.h"
#include "controllers/dashboardcontroller.h"
#include "infrastructure/filecontentservice.h"
#include <controllers/rootcontroller.h>
#include <controllers/actioncontroller.h>

void ApiMock::ConfigureDependencies() {
	ServiceRegistry::Register<ContentService>(new FileContentService);
}

void ApiMock::ConfigureRoutes(RouteRegistry* routes) {
	routes->registerRoute(RoutingTemplate("/"), new ActionController([](Controller* base, RequestData request)
	{
		return base->createResponse(HTTP_MOVED_PERMANENTLY, {
			{ "Location", "/dashboard" }
		});
	}));

	routes->registerRoute(RoutingTemplate("/dashboard"), new DashboardController(
		ServiceRegistry::Resolve<ContentService>()));

	routes->registerRoute(RoutingTemplate("/*"), new RootController(
		ServiceRegistry::Resolve<ContentService>()));
}