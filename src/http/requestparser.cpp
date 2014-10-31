#include "RequestParser.h"
#include <sstream>
#include <vector>

std::vector<std::string> ApiMock::RequestParser::projectToCollection(std::string const& request) {
	const std::string CRLF = "\r\n";
	std::vector<std::string> fromRequest;
	std::string::size_type pos = 0;
	std::string::size_type prev = 0;

	while ((pos = request.find(CRLF, prev)) != std::string::npos) {
		fromRequest.push_back(request.substr(prev, pos - prev));
		prev = pos + 1;
	}

	fromRequest.push_back(request.substr(prev));
	return fromRequest;
}

ApiMock::RequestData ApiMock::RequestParser::parse(std::string const& requestBuffer) {
	std::vector<std::string> entireRequest = projectToCollection(requestBuffer);
	RequestData request;

	return request;
}