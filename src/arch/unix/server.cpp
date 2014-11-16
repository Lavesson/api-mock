#include "core/server.h"

struct ApiMock::Server::ServerImpl {
    // ...
};

ApiMock::Server::Server() {

}

ApiMock::Server::~Server() {

}

void ApiMock::Server::initialize(const std::string& address, int port, int bufferSize) {

}

bool ApiMock::Server::acceptNext(IncomingRequest** incoming) {

}

void ApiMock::Server::close(IncomingRequest* incoming) {

}

