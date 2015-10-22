#pragma once
#include <string>
#include <unordered_map>
#include "statuscodes.h"

namespace ApiMock {
	struct ResponseData {
		typedef std::unordered_map<std::string, std::string> Headers;

		std::string body;
		Headers headers;
		HTTP_RESPONSE_CODE statusCode;

		bool successfulStatusCode() const;
		std::string toString() const;
	};

	inline bool ResponseData::successfulStatusCode() const {
		return statusCode >= HTTP_OK && statusCode < HTTP_MULTIPLE_CHOICES;
	}

	inline std::string ResponseData::toString() const {
		return "Server responded with " + std::to_string(statusCode);
	}
}
