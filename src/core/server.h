#ifndef	APIMOCK_CORE_SERVER_H
#define APIMOCK_CORE_SERVER_H
#include <string>
#include <memory>

class Server {
	struct ServerImpl;
	std::unique_ptr<ServerImpl> _impl;

	Server& operator=(const Server&);
	Server(const Server&);

public:
	Server();
	~Server();
	void startServer(const std::string& address, int port, int bufferSize);
};

#endif