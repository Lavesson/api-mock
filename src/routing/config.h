#ifndef	APIMOCK_CONFIG_H
#define APIMOCK_CONFIG_H

namespace ApiMock {
	class RouteRegistry;
	void ConfigureDependencies();
	void ConfigureRoutes(RouteRegistry* routes);
}

#endif