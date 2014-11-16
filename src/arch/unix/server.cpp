/*
 * Sockets server using Berkeley/POSIX sockets
 */
 
#include "core/server.h"
#include "core/exceptions.h"
#include "core/incomingrequest.h"

#define SOCKET int

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>  
#include <string.h>

namespace ApiMock {
    class PosixSocketRequest : public IncomingRequest {
    	SOCKET _client;
		std::string _requestString;
		
	public:
		PosixSocketRequest(SOCKET client, std::string requestString)
			: _client(client), _requestString(requestString) {}

		~PosixSocketRequest() {
			close(_client);
		}
		
        std::string getRequestAsString() {
			return _requestString;
        }
        
		void sendResponse(const std::string& responseAsString) {
			send(_client, responseAsString.c_str(), responseAsString.length(), 0);
		}
    };
}

struct ApiMock::Server::ServerImpl {
	SOCKET _sock;
	int _bufferSize;
	sockaddr_in _sockAddr;
	
	void createSocket(const std::string& address, int port) {
		_sockAddr.sin_family = AF_INET;
		_sockAddr.sin_port = htons(port);
		_sockAddr.sin_addr.s_addr = inet_addr(address.c_str());
		_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}
	
	void setup(const std::string& address, int port, int bufferSize) {
		_bufferSize = bufferSize;

		tryToCreateSocket(address, port);
		tryToBindSocket();
	}
	
	void tryToCreateSocket(const std::string& address, int port) {
		createSocket(address, port);
		
		if (_sock < 0) {
			throw SocketException("Could not create socket");
		}
	}
	
	bool bindingFailed() {
		auto r = bind(
			_sock,
			reinterpret_cast<sockaddr*>(&_sockAddr),
			sizeof(_sockAddr));

		return r < 0;
	}
	
	void tryToBindSocket() {
    	if (bindingFailed())
			throw SocketException("Could not bind socket");
	}
	
	std::string getRequestString(SOCKET client) {
		int result = 0;
		char* buffer = new char[_bufferSize];
		memset(buffer, 0, _bufferSize);

		result = recv(client, buffer, _bufferSize, 0);
		std::string request(buffer);
		delete buffer;
		return request;
	}

	bool acceptNext(IncomingRequest** request) {
	    auto result = listen(_sock, SOMAXCONN);
		auto client = accept(_sock, nullptr, nullptr);

		if (client < 0) 
			return false;

		if (result < 0)
			throw SocketException("Accepting a socket failed");

		*request = new PosixSocketRequest(
			client, getRequestString(client));

		return true;
	}
};

ApiMock::Server::Server() 
    : _impl(new ServerImpl) {}

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

