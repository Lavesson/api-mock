#include "rootcontroller.h"
#include "serialization/result.h"
#include "infrastructure/exceptions.h"

ApiMock::RootController::RootController(ContentService* content)
	: _content(content) {}

ApiMock::ResponseData ApiMock::RootController::get(RequestData request) {
	auto filename = request.get["@wildcard"];

	try {
		auto c = _content->getContent("www/app/" + filename);
		RawResult result(c.content, c.mimeType);
		return createResponse(HTTP_OK, &result);
	}
	catch (FileNotFoundException e) {
		RawResult result("", "text/plain");
		return createResponse(HTTP_NOT_FOUND, &result);
	}
}