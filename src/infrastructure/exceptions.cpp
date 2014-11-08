#include "infrastructure/exceptions.h"

ApiMock::FileNotFoundException::FileNotFoundException(std::string const& filename) : _filename(filename) {
}

char const* ApiMock::FileNotFoundException::what() const {
	return _filename.c_str();
}