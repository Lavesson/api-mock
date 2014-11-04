#include "result.h"

ApiMock::PureTextResult::PureTextResult(std::string const& payload, std::string const& mime)
	: _payload(payload), _mime(mime) {}

std::string ApiMock::PureTextResult::getMimeType() {
	return _mime;
}

std::string ApiMock::PureTextResult::getSerializedResult() {
	return _payload;
}