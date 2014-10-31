#include "core/server.h"
#include "core/exceptions.h"
#include "core/incomingrequest.h"
#include <windows.h>
#include <winsock.h>

#define VERSION_WINSOCK2 0x0202
#pragma comment(lib, "wsock32.lib")

namespace ApiMock {
	class WinSockRequest : public IncomingRequest {
		SOCKET _client;
		std::string _requestString;

	public:
		WinSockRequest(SOCKET client, std::string requestString)
			: _client(client), _requestString(requestString) {}

		~WinSockRequest() {
			closesocket(_client);
		}

		std::string getRequestAsString() override {
			return _requestString;
		}

		void sendResponse(std::string const& responseAsString) override {
			send(_client, responseAsString.c_str(), responseAsString.length(), 0);
		}
	};
}

struct ApiMock::Server::ServerImpl {
	SOCKET _sock;
	WSADATA _wsaOptions;
	SOCKADDR_IN _sockAddr;
	int _bufferSize;

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

	std::string getRequestString(SOCKET client) {
		int result = 0;
		char* buffer = new char[_bufferSize];
		ZeroMemory(buffer, _bufferSize);

		result = recv(client, buffer, _bufferSize, 0);
		std::string request(buffer);
		delete buffer;
		return request;
	}

	bool acceptNext(IncomingRequest** request) {
		auto result = listen(_sock, SOMAXCONN);
		auto client = accept(_sock, nullptr, nullptr);

		if (!client) 
			return false;

		if (result == SOCKET_ERROR) {
			printLastErrorToStdErr();
			throw SocketException("Accepting a socket failed");
		}

		*request = new WinSockRequest(
			client, getRequestString(client));

		return true;
	}

	void setup(const std::string& address, int port, int bufferSize) {
		_bufferSize = bufferSize;

		makeSureSocketsStarted(
			WSAStartup(VERSION_WINSOCK2, &_wsaOptions));

		tryToCreateSocket(address, port);
		tryToBindSocket();
	}

	~ServerImpl() {
		if (_sock) closesocket(_sock);
		WSACleanup();
	}
};

ApiMock::Server::Server() : _impl(new ServerImpl) {}
ApiMock::Server::~Server() {}

void ApiMock::Server::initialize(const std::string& address, int port, int bufferSize) {
	_impl->setup(address, port, bufferSize);
}

bool ApiMock::Server::acceptNext(IncomingRequest** incoming) {
	return _impl->acceptNext(incoming);
}

void ApiMock::Server::close(IncomingRequest* incoming) {
	delete incoming;
}