#include "exceptions.h"

SocketException::SocketException(std::string const& problem) 
	: _problem(problem) {}

char const* SocketException::what() const {
	return _problem.c_str();
}