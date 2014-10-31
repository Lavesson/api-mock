#ifndef APIMOCK_REQUESTPARSER_H
#define APIMOCK_REQUESTPARSER_H
#include "http/RequestData.h"
#include <string>
#include <vector>
#include <unordered_map>

namespace ApiMock {
	class RequestParser {
		typedef std::unordered_map<std::string, RequestData::METHOD> RequestCollection;
		RequestCollection _methods;

		void parseHeader(RequestData* request, const std::string& headerStr);
		void parseRequestBody(RequestData* request, std::vector<std::string> requestLines, int offset);
		void parseRequestLine(RequestData* request, const std::string& requestLine);
		const std::string CRLF = "\r\n";

	public:
		RequestParser();
		std::vector<std::string> projectToCollection(const std::string& request);
		RequestData parse(const std::string& requestBuffer);
	};
}

#endif