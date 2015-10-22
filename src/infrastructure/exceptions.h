#pragma once
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
