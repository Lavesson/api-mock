#include "exceptions.h"

ApiMock::SocketException::SocketException(std::string const& problem) 
	: _problem(problem) {}

char const* ApiMock::SocketException::what() const {
	return _problem.c_str();
}