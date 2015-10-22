#pragma once
#include <string>
#include <http/statuscodes.h>
#include "responsedata.h"

namespace ApiMock {
	struct ResponseData;

	class ResponseSerializer {
	private:
		std::string statusCodeDescription(HTTP_RESPONSE_CODE responseCode);

	public:
		std::string serialize(ResponseData response_data);
	};
}
