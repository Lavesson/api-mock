#pragma once
#include "http/requestdata.h"
#include "http/responsedata.h"

namespace ApiMock {
	enum HTTP_RESPONSE_CODE;
	class Result;

	class Controller {
	private:
		void augmentHeaders(ResponseData* responseData, const ResponseData::Headers& customHeaders);

	public:
		virtual ~Controller() {}

		ResponseData createResponse(HTTP_RESPONSE_CODE statusCode);
		ResponseData createResponse(HTTP_RESPONSE_CODE statusCode, Result* payload);
				
		ResponseData createResponse(HTTP_RESPONSE_CODE statusCode, const ResponseData::Headers& customHeaders);
		ResponseData createResponse(HTTP_RESPONSE_CODE statusCode, Result* payload, const ResponseData::Headers& customHeaders);

		virtual ResponseData get(RequestData request);
		virtual ResponseData put(RequestData request);
		virtual ResponseData del(RequestData request);
		virtual ResponseData post(RequestData request);
	};
}
