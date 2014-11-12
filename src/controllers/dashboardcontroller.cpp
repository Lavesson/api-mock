#include "dashboardcontroller.h"
#include "serialization/result.h"
#include "infrastructure/contentservice.h"
#include <fstream>
#include <infrastructure/exceptions.h>


ApiMock::DashboardController::DashboardController(ContentService* content)
	: _content(content) {}

ApiMock::ResponseData ApiMock::DashboardController::get(RequestData request) {
	try {
		auto content = _content->getContent("www/app/index.html");
		RawResult c(content.content, content.mimeType);
		return createResponse(HTTP_OK, &c);
	}
	catch (FileNotFoundException e) {
		return createResponse(HTTP_NOT_FOUND);
	}
}