#include "httpserver.h"
#include "resourcestrategy.h"
#include "requestparser.h"
#include "responseserializer.h"
#include "core/incomingrequest.h"
#include <string>

ApiMock::HttpServer::HttpServer() {}
ApiMock::HttpServer::~HttpServer() {}

void ApiMock::HttpServer::startServer(std::string const& address, int port, int bufferSize, ResourceStrategy* resourceStrategy) {
	server.initialize(address, port, bufferSize);
	IncomingRequest* incoming = nullptr;
	RequestParser rp;
	ResponseSerializer rs;
	
	while (server.acceptNext(&incoming)) {
		auto request = rp.parse(incoming->getRequestAsString());
		auto response = resourceStrategy->createResponse(request);
		
		incoming->sendResponse(rs.serialize(response));
		server.close(incoming);
	}
}