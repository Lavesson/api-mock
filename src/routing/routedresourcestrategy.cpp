#include "routedresourcestrategy.h"
#include "routingtemplate.h"
#include "controllers/controller.h"

void ApiMock::RoutedResourceStrategy::registerRoute(RoutingTemplate route, Controller* ctrl) {
	_routeMap.insert(
		std::make_pair(route, ctrl));
}

ApiMock::Controller* ApiMock::RoutedResourceStrategy::matchRoute(const std::string& uri) {
	return nullptr;
}

ApiMock::ResponseData ApiMock::RoutedResourceStrategy::errorResponse(HTTP_RESPONSE_CODE status) {
	ResponseData response;
	response.statusCode = status;
	response.body = "";
	response.headers["Connection"] = "Close";
	return response;
}

ApiMock::ResponseData ApiMock::RoutedResourceStrategy::createResponse(RequestData const& request) {
	auto route = matchRoute(request.requestUri);

	if (!route) return errorResponse(HTTP_NOT_FOUND);

	ResponseData r;

	switch (request.method) {
	case RequestData::GET: route->get(request); break;
	case RequestData::POST: route->post(request); break;
	case RequestData::PUT: route->put(request); break;
	case RequestData::DELETE: route->del(request); break;
	default: return errorResponse(HTTP_METHOD_NOT_ALLOWED);
	}

	return r;
}