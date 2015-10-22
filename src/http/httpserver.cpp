#include "httpserver.h"
#include "resourcestrategy.h"
#include "requestparser.h"
#include "responseserializer.h"
#include "core/incomingrequest.h"
#include <string>
#include <algorithm>

ApiMock::HttpServer::HttpServer(bool verbose) : isVerbose(verbose) {}
ApiMock::HttpServer::~HttpServer() {}

void ApiMock::HttpServer::startServer(std::string const& address, int port, int bufferSize, ResourceStrategy* resourceStrategy) {

	server.initialize(address, port, bufferSize);
	IncomingRequest* incoming = nullptr;
	RequestParser rp;
	ResponseSerializer rs;

	logVerboseLine("Verbose mode enabled");

	while (server.acceptNext(&incoming)) {
		auto requestString = incoming->getRequestAsString();
		auto delimPoint = requestString.find_first_of("\n");
		logVerboseLine(requestString.substr(0, delimPoint));
		auto request = rp.parse(requestString);
		auto response = resourceStrategy->createResponse(request);
		
		incoming->sendResponse(rs.serialize(response));
		server.close(incoming);
	}
}

void ApiMock::HttpServer::logVerboseLine(const std::string& output) {
	if (isVerbose)
		printf("%s\n", output.c_str());
}
