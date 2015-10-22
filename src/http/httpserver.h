#ifndef	APIMOCK_HTTPSERVER_H
#define APIMOCK_HTTPSERVER_H
#include <memory>
#include <string>
#include "core/server.h"

namespace ApiMock {
	class ResourceStrategy;

	class HttpServer {
		Server server;
		HttpServer& operator=(const HttpServer&);
		HttpServer(const HttpServer&);
		bool isVerbose;

	public:
		explicit HttpServer(bool verbose);
		~HttpServer();
		void startServer(const std::string& address, int port, int bufferSize, ResourceStrategy* resourceStrategy);

		void logVerboseRequest(RequestData request);
		void logVerboseLine(const std::string &output);

		void logVerboseResponseIfNotSuccess(const ResponseData &response);
	};
}

#endif