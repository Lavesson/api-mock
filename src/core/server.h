#ifndef	APIMOCK_CORE_SERVER_H
#define APIMOCK_CORE_SERVER_H
#include <string>

class Server {
public:
	void startServer(std::string address, int port);
};

#endif