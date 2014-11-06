#include "rootcontroller.h"
#include "serialization/result.h"

ApiMock::RootController::RootController(ContentService* content)
	: _content(content) {}

ApiMock::ResponseData ApiMock::RootController::get(RequestData request) {
	auto filename = request.get["@wildcard"];
	auto c = _content->getContent("www/" + filename);
	RawResult result(c.content, c.mimeType);
	return createResponse(HTTP_OK, &result);
}