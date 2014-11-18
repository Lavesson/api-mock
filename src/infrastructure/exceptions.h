#ifndef APIMOCK_INFRA_EXCEPTIONS_H
#define APIMOCK_INFRA_EXCEPTIONS_H
#include <exception>
#include <string>

namespace ApiMock {
	class FileNotFoundException : public std::exception {
	private:
		std::string _filename;

	public:
		explicit FileNotFoundException(const std::string& filename);
		const char* what() const throw() override;
	};
}

#endif