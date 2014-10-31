#include "RequestParser.h"
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <ctype.h>

std::string trim(std::string s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(isspace))));
	return s;
}

std::string toLower(std::string s) {
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
	return s;
}

void ApiMock::RequestParser::parseHeader(RequestData* request, const std::string& headerStr) {
	auto splitAt = headerStr.find(':');
	auto headerName = toLower(headerStr.substr(0, splitAt));
	auto headerValue = toLower(trim(headerStr.substr(splitAt + 1)));

	request->headers.insert(
		std::make_pair(headerName, headerValue));
}

void ApiMock::RequestParser::parseRequestBody(RequestData* request, std::vector<std::string> requestLines, int offset) {
	// TODO
}

void ApiMock::RequestParser::parseRequestLine(RequestData* request, const std::string& requestLine) {
	std::stringstream ss(requestLine);
	std::string method;
	std::string uri;
	std::string version;

	ss >> method;
	ss >> uri;
	ss >> version;

	request->httpVersion = RequestData::HTTP_1_1;
	request->requestUri = uri;

	if (_methods.find(method) != _methods.end())
		request->method = _methods[method];
}

ApiMock::RequestParser::RequestParser() {
	_methods.insert(std::make_pair("GET", RequestData::GET));
	_methods.insert(std::make_pair("POST", RequestData::POST));
	_methods.insert(std::make_pair("PUT", RequestData::PUT));
	_methods.insert(std::make_pair("DELETE", RequestData::DELETE));
}

std::vector<std::string> ApiMock::RequestParser::projectToCollection(const std::string& request) {
	std::vector<std::string> fromRequest;
	std::string::size_type pos = 0;
	std::string::size_type prev = 0;

	while ((pos = request.find(CRLF, prev)) != std::string::npos) {
		fromRequest.push_back(request.substr(prev, pos - prev));
		prev = pos + CRLF.length();
	}

	fromRequest.push_back(request.substr(prev));
	return fromRequest;
}

ApiMock::RequestData ApiMock::RequestParser::parse(const std::string& requestBuffer) {
	std::vector<std::string> r = projectToCollection(requestBuffer);
	RequestData request;
	parseRequestLine(&request, r[0]);

	for (int i = 1; i < r.size(); ++i) {
		if (r[i] == "") {
			parseRequestBody(&request, r, i + 1);
			break;
		}

		parseHeader(&request, r[i]);
	}

	return request;
}