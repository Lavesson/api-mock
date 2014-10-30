#include "core/server.h"
#include "core/exceptions.h"
#include "http/RequestParser.h"
#include <windows.h>
#include <winsock.h>

#define VERSION_WINSOCK2 0x0202
#pragma comment(lib, "wsock32.lib")

struct ApiMock::Server::ServerImpl {
	SOCKET _sock;
	WSADATA _wsaOptions;
	SOCKADDR_IN _sockAddr;

	void makeSureSocketsStarted(int err) {
		if (err)
			throw SocketException("Something went wrong when starting WinSock. The error code was: " + std::to_string(err));

		if (_wsaOptions.wVersion != VERSION_WINSOCK2)
			throw SocketException("Expected WinSock 2.0, but the reported version was: " + std::string(_wsaOptions.szDescription));
	}

	void createSocket(const std::string& address, int port) {
		_sockAddr.sin_family = AF_INET;
		_sockAddr.sin_port = htons(port);
		_sockAddr.sin_addr.s_addr = inet_addr(address.c_str());
		_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}

	void tryToCreateSocket(const std::string& address, int port) {
		createSocket(address, port);

		if (_sock == INVALID_SOCKET) {
			printLastErrorToStdErr();
			throw SocketException("Could not create socket");
		}
	}

	bool bindingFailed() {
		auto r = bind(
			_sock,
			reinterpret_cast<LPSOCKADDR>(&_sockAddr),
			sizeof(_sockAddr));

		return r == SOCKET_ERROR || r == INVALID_SOCKET;
	}

	void printLastErrorToStdErr() {
		wchar_t *s = nullptr;
		FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr, WSAGetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			reinterpret_cast<LPTSTR>(&s), 0, nullptr);

		fprintf(stderr, "%S", s);
		LocalFree(s);
	}

	void tryToBindSocket() {
		if (bindingFailed()) {
			printLastErrorToStdErr();
			throw SocketException("Could not bind socket");
		}
	}

	void handleRequest(SOCKET client, int bufferSize, CreateResponse createResponse) {
		int result = 0;
		char* buffer = new char[bufferSize];
		ZeroMemory(buffer, bufferSize);
		RequestParser rqp;

		do {
			result = recv(client, buffer, bufferSize, 0);
			auto request = rqp.parse(std::string(buffer));

			createResponse(request);

			// Send a small response
			std::string response = "<h1>It works!</h1>";
			send(client, response.c_str(), response.length(), 0);
			closesocket(client);
		} while (result > 0);

		delete buffer;
	}

	void startListening(int bufferSize, CreateResponse createResponse) {
		auto result = listen(_sock, SOMAXCONN);
		
		// Handle incoming requests as they occur
		while (auto client = accept(_sock, nullptr, nullptr)) {
			if (result == SOCKET_ERROR) {
				printLastErrorToStdErr();
				throw SocketException("Accepting a socket failed");
			}

			handleRequest(client, bufferSize, createResponse);
		}
	}

	void listenTo(const std::string& address, int port, int bufferSize, CreateResponse createResponse) {
		makeSureSocketsStarted(
			WSAStartup(VERSION_WINSOCK2, &_wsaOptions));

		tryToCreateSocket(address, port);
		tryToBindSocket();
		startListening(bufferSize, createResponse);
	}

	~ServerImpl() {
		if (_sock) closesocket(_sock);
		WSACleanup();
	}
};

ApiMock::Server::Server() : _impl(new ServerImpl) {}
ApiMock::Server::~Server() {}

void ApiMock::Server::startServer(const std::string& address, int port, int bufferSize, CreateResponse createResponse) {
	_impl->listenTo(address, port, bufferSize, createResponse);
}
