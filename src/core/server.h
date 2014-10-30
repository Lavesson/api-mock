#ifndef	APIMOCK_SERVER_H
#define APIMOCK_SERVER_H
#include <string>
#include <memory>
#include <functional>
#include "http/requestdata.h"
#include "http/responsedata.h"

namespace ApiMock {
	class Server {
		typedef std::function<void(RequestData)> CreateResponse;
		struct ServerImpl;
		std::unique_ptr<ServerImpl> _impl;

		Server& operator=(const Server&);
		Server(const Server&);

	public:
		Server();
		~Server();
		void startServer(const std::string& address, int port, int bufferSize, CreateResponse createResponse);
	};
}

#endif