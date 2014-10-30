#ifndef APIMOCK_REQUESTPARSER_H
#define APIMOCK_REQUESTPARSER_H
#include "http/RequestData.h"
#include <string>
#include <vector>

namespace ApiMock {
	class RequestParser {
	public:
		std::vector<std::string> projectToCollection(const std::string& request);
		RequestData parse(const std::string& requestBuffer);
	};
}

#endif