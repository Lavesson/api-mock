#include "exceptions.h"

ApiMock::SocketException::SocketException(std::string const& problem) 
	: _problem(problem) {}

const char* ApiMock::SocketException::what() const throw() {
    return _problem.c_str();
}

ApiMock::UnknownFlagException::UnknownFlagException(const std::string &flag) : _flag(flag) {}

const char* ApiMock::UnknownFlagException::what() const throw() {
    return std::string("Unknown flag: " + _flag).c_str();
}
