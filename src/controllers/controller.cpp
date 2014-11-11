#include "controller.h"
#include "http/responsedata.h"
#include "http/requestdata.h"
#include "serialization/result.h"

void ApiMock::Controller::augmentHeaders(ResponseData* responseData, const ResponseData::Headers& customHeaders) {
	for (auto& header : customHeaders)
		responseData->headers[header.first] = header.second;
}

ApiMock::ResponseData ApiMock::Controller::createResponse(HTTP_RESPONSE_CODE statusCode, const ResponseData::Headers& customHeaders) {
	ResponseData response;

	response.body = "";
	response.headers["Content-Length"] = "0";
	response.statusCode = statusCode;
	augmentHeaders(&response, customHeaders);
	return response;
}

ApiMock::ResponseData ApiMock::Controller::createResponse(HTTP_RESPONSE_CODE statusCode, Result* payload, const ResponseData::Headers& customHeaders) {
	ResponseData response;

	response.body = payload->getSerializedResult();
	response.headers["Content-Length"] = std::to_string(response.body.length());
	response.headers["Content-Type"] = payload->getMimeType();
	response.statusCode = statusCode;
	augmentHeaders(&response, customHeaders);
	return response;
}


ApiMock::ResponseData ApiMock::Controller::get(RequestData request) {
	return createResponse(HTTP_METHOD_NOT_ALLOWED);
}

ApiMock::ResponseData ApiMock::Controller::put(RequestData request) {
	return createResponse(HTTP_METHOD_NOT_ALLOWED);
}

ApiMock::ResponseData ApiMock::Controller::del(RequestData request) {
	return createResponse(HTTP_METHOD_NOT_ALLOWED);
}

ApiMock::ResponseData ApiMock::Controller::post(RequestData request) {
	return createResponse(HTTP_METHOD_NOT_ALLOWED);
}