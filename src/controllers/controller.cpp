#include "controller.h"
#include "http/responsedata.h"
#include "http/requestdata.h"

ApiMock::ResponseData ApiMock::Controller::createResponse(HTTP_RESPONSE_CODE statusCode) {
	ResponseData response;

	response.body = "";
	response.headers["Content-Length"] = "0";
	response.statusCode = statusCode;

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