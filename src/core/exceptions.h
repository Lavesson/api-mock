#ifndef APIMOCK_EXCEPTIONS_H
#define APIMOCK_EXCEPTIONS_H
#include <exception>
#include <string>

class SocketException : public std::exception {
private:
	std::string _problem;

public:
	SocketException(const std::string& problem);
	char const* what() const override;
};

#endif