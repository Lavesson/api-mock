#ifndef APIMOCK_RESPONSEDATA_H
#define APIMOCK_RESPONSEDATA_H

#include <string>
#include <unordered_map>
#include "statuscodes.h"

namespace ApiMock {
	struct ResponseData {
		std::string body;
		std::unordered_map<std::string, std::string> headers;
		HTTP_RESPONSE_CODE statusCode;
	};
}

#endif