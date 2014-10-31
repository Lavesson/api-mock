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
		incoming->sendResponse("<h1>It works!</h1>");
		server.close(incoming);
	}
}