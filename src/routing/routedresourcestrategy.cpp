#include "routedresourcestrategy.h"
#include "routingtemplate.h"

void ApiMock::RoutedResourceStrategy::registerRoute(RoutingTemplate route, Controller* ctrl) {
	_routeMap.insert(
		std::make_pair(route, std::unique_ptr<Controller>(ctrl)));
}

ApiMock::Controller* ApiMock::RoutedResourceStrategy::matchRoute(const std::string& uri) {
	for (auto& r : _routeMap)
		if (r.first.isMatch(uri)) return r.second.get();

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
	auto controller = matchRoute(request.requestUri);

	if (!controller)
		return errorResponse(HTTP_NOT_FOUND);

	switch (request.method) {
	case RequestData::GET:		return controller->get(request);
	case RequestData::POST:		return controller->post(request);
	case RequestData::PUT:		return controller->put(request);
	case RequestData::DELETE:	return controller->del(request);
	default:					return errorResponse(HTTP_METHOD_NOT_ALLOWED);
	}
}