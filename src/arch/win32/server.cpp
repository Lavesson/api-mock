#include "core/server.h"
#include "core/exceptions.h"
#include <windows.h>
#include <winsock.h>

#define VERSION_WINSOCK2 0x0202
#pragma comment(lib, "wsock32.lib")

struct Server::ServerImpl {
	SOCKET s;
	WSADATA w;

	void listen(int port) {
		auto err = WSAStartup(VERSION_WINSOCK2, &w);
		
		if (err) 
			throw SocketException("Something went wrong when starting WinSocks. The error code was: " + std::to_string(err) + "\n");

		if (w.wVersion != VERSION_WINSOCK2)
			throw SocketException("Expected WinSock 2.0, but the reported version was: " + std::string(w.szDescription) + "\n");
	}

	~ServerImpl() {
		WSACleanup();
	}
};

Server::Server() : _impl(new ServerImpl) {}
Server::~Server() {}

void Server::startServer(std::string address, int port) {
	_impl->listen(80);
}
