#ifndef	APIMOCK_CONTROLLER_H
#define APIMOCK_CONTROLLER_H

#include "http/requestdata.h"
#include "http/responsedata.h"

namespace ApiMock {
	enum HTTP_RESPONSE_CODE;

	class Controller {
	public:
		virtual ~Controller() {}
		
		ResponseData createResponse(HTTP_RESPONSE_CODE statusCode);

		virtual ResponseData get(RequestData request);
		virtual ResponseData put(RequestData request);
		virtual ResponseData del(RequestData request);
		virtual ResponseData post(RequestData request);
	};
}

#endif