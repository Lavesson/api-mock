#ifndef	APIMOCK_HTTPSERVER_H
#define APIMOCK_HTTPSERVER_H
#include <memory>
#include <string>
#include "core/server.h"

namespace ApiMock {
	class HttpServer {
		Server server;
		HttpServer& operator=(const HttpServer&);
		HttpServer(const HttpServer&);

	public:
		HttpServer();
		~HttpServer();
		typedef std::function<ResponseData(RequestData)> CreateResponse;
		void startServer(const std::string& address, int port, int bufferSize, CreateResponse createResponse);
	};
}

#endif