#include "exceptions.h"

ApiMock::SocketException::SocketException(std::string const& problem) 
	: _problem(problem) {}

const char* ApiMock::SocketException::what() const noexcept {
    return _problem.c_str();
}
