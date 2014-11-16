#include "routedresourcestrategy.h"
#include "routingtemplate.h"
#include "routedictionary.h"

void ApiMock::RoutedResourceStrategy::registerRoute(RoutingTemplate route, Controller* ctrl) {
	_routeMap.insert(
		std::make_pair(route, std::unique_ptr<Controller>(ctrl)));
}

ApiMock::Controller* ApiMock::RoutedResourceStrategy::matchRoute(RequestData* request) {
	Controller* ctrl = nullptr;
	auto uri = request->requestUri;

	/* Match routes in appearing order until encountering a working one */
	for (auto& r : _routeMap) {
		if (r.first.isMatch(uri)) {
			ctrl = r.second.get();
			RouteDictionary::Inject(r.first.getTemplate(), request);
			break;
		}
	}

	return ctrl;
}

ApiMock::ResponseData ApiMock::RoutedResourceStrategy::errorResponse(HTTP_RESPONSE_CODE status) {
	ResponseData response;
	response.statusCode = status;
	response.body = "";
	response.headers["Connection"] = "Close";
	return response;
}

ApiMock::ResponseData ApiMock::RoutedResourceStrategy::createResponse(const RequestData& request) {
	RequestData augmRequest = request;
	auto controller = matchRoute(&augmRequest);

	if (!controller)
		return errorResponse(HTTP_NOT_FOUND);

	switch (augmRequest.method) {
	case RequestData::GET:		return controller->get(augmRequest);
	case RequestData::POST:		return controller->post(augmRequest);
	case RequestData::PUT:		return controller->put(augmRequest);
	case RequestData::DELETE:	return controller->del(augmRequest);
	default:					return errorResponse(HTTP_METHOD_NOT_ALLOWED);
	}
}

