#include "routingtemplate.h"

bool ApiMock::RoutingTemplate::operator==(const RoutingTemplate& other) const {
	return (other._routeTemplate == _routeTemplate);
}

ApiMock::RoutingTemplate::RoutingTemplate(std::string const& routeTemplate) 
	: _routeTemplate(routeTemplate) {}

std::string ApiMock::RoutingTemplate::getTemplate() const {
	return _routeTemplate;
}