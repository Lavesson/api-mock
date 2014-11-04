#include "result.h"

ApiMock::RawResult::RawResult(std::string const& payload, std::string const& mime)
	: _payload(payload), _mime(mime) {}

std::string ApiMock::RawResult::getMimeType() {
	return _mime;
}

std::string ApiMock::RawResult::getSerializedResult() {
	return _payload;
}