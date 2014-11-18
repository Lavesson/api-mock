#ifndef APIMOCK_CORE_EXCEPTIONS_H
#define APIMOCK_CORE_EXCEPTIONS_H
#include <exception>
#include <string>

namespace ApiMock {
	class SocketException : public std::exception {
	private:
		std::string _problem;

	public:
		explicit SocketException(const std::string& problem);
        const char* what() const throw() override;
    };
}

#endif