#include "httpserver.h"
#include "requestparser.h"
#include "responseserializer.h"
#include "core/incomingrequest.h"
#include <string>

ApiMock::HttpServer::HttpServer() {}
ApiMock::HttpServer::~HttpServer() {}

void ApiMock::HttpServer::startServer(std::string const& address, int port, int bufferSize, CreateResponse createResponse) {
	server.initialize(address, port, bufferSize);
	IncomingRequest* incoming = nullptr;
	RequestParser rp;
	ResponseSerializer rs;
	
	while (server.acceptNext(&incoming)) {
		auto request = rp.parse(incoming->getRequestAsString());
		auto response = createResponse(request);
		
		incoming->sendResponse(rs.serialize(response));
		server.close(incoming);
	}
}