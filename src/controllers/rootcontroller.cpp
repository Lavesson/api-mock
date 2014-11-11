#include "rootcontroller.h"
#include "serialization/result.h"
#include "infrastructure/exceptions.h"

ApiMock::RootController::RootController(ContentService* content)
	: _content(content) {}

ApiMock::ResponseData ApiMock::RootController::get(RequestData request) {
	RawResult result("", "text/plain");

	if (request.get.find("@wildcard") == request.get.end())
		return createResponse(HTTP_NOT_FOUND, &result);

	auto filename = request.get["@wildcard"];

	try {
		auto c = _content->getContent("www/app/" + filename);
		RawResult result(c.content, c.mimeType);
		return createResponse(HTTP_OK, &result);
	}
	catch (FileNotFoundException e) {
		return createResponse(HTTP_NOT_FOUND, &result);
	}
}