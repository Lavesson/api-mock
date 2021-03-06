#include "infrastructure/exceptions.h"

ApiMock::FileNotFoundException::FileNotFoundException(std::string const& filename) : _filename(filename) {
}

const char* ApiMock::FileNotFoundException::what() const throw() {
	return _filename.c_str();
}