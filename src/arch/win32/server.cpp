#include "core/server.h"
#include "core/exceptions.h"
#include <windows.h>
#include <winsock.h>

#define VERSION_WINSOCK2 0x0202
#pragma comment(lib, "wsock32.lib")

struct Server::ServerImpl {
	SOCKET s;
	WSADATA w;

	void makeSureSocketsStarted(int err) {
		if (err)
			throw SocketException("Something went wrong when starting WinSock. The error code was: " + std::to_string(err) + "\n");

		if (w.wVersion != VERSION_WINSOCK2)
			throw SocketException("Expected WinSock 2.0, but the reported version was: " + std::string(w.szDescription) + "\n");
	}

	void listen(std::string address, int port) {
		makeSureSocketsStarted(
			WSAStartup(VERSION_WINSOCK2, &w));

		SOCKADDR_IN sockData;
		sockData.sin_family = AF_INET;
		sockData.sin_port = htons(port);
		sockData.sin_addr.s_addr = htonl(inet_addr(address.c_str()));
	}

	~ServerImpl() {
		WSACleanup();
	}
};

Server::Server() : _impl(new ServerImpl) {}
Server::~Server() {}

void Server::startServer(std::string address, int port) {
	_impl->listen(address, port);
}
