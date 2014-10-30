#include "responseserializer.h"
#include "responsedata.h"
#include <sstream>

std::string ApiMock::ResponseSerializer::serialize(ResponseData response) {
	const std::string CRLF = "\r\n";
	std::stringstream ss;

	return ss.str();
}