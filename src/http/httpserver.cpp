#include "httpserver.h"
#include "resourcestrategy.h"
#include "requestparser.h"
#include "responseserializer.h"
#include "core/incomingrequest.h"
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
		auto request = rp.parse(requestString);
		logVerboseRequest(request);
		auto response = resourceStrategy->createResponse(request);
		incoming->sendResponse(rs.serialize(response));
		logVerboseResponseIfNotSuccess(response);
		server.close(incoming);
	}
}


void ApiMock::HttpServer::logVerboseRequest(RequestData request) {
	ApiMock::HttpServer::logVerboseLine(request.toString());
}

void ApiMock::HttpServer::logVerboseLine(const std::string& output) {
	if (isVerbose)
		printf("%s\n", output.c_str());
}

void ApiMock::HttpServer::logVerboseResponseIfNotSuccess(const ApiMock::ResponseData &response) {
	if (!response.successfulStatusCode()) {
		logVerboseLine(response.toString());
	}
}
