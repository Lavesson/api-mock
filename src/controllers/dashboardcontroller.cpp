#include "dashboardcontroller.h"
#include "serialization/result.h"
#include "infrastructure/contentservice.h"
#include <fstream>

ApiMock::DashboardController::DashboardController(ContentService* content)
	: _content(content) {}

ApiMock::ResponseData ApiMock::DashboardController::get(RequestData request) {
	auto content = _content->getContent(request.requestUri);
	PureTextResult c(content.content, content.mimeType);
	return createResponse(HTTP_OK, &c);
}