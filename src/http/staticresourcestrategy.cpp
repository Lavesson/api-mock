#include "staticresourcestrategy.h"

ApiMock::ResponseData ApiMock::StaticResourceStrategy::createResponse(RequestData const& request) {
	ResponseData response;
	response.body = "{ \"application\" : \"ApiMock\", \"version\" : \"2014.10.31\" }";
	response.headers["Content-Type"] = "application/json";
	response.headers["Content-Length"] = std::to_string(response.body.length());
	response.statusCode = ApiMock::HTTP_OK;
	return response;
}