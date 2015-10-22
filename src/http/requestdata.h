#ifndef APIMOCK_REQUESTDATA_H
#define APIMOCK_REQUESTDATA_H

#include <string>
#include <unordered_map>
#include "routing/routedictionary.h"

namespace ApiMock {
	struct RequestData {
		enum HTTP_VERSION {
			HTTP_1_1,
		} httpVersion;

		enum METHOD {
			GET,
			POST,
			PUT,
			DELETE,
		} method;

		std::string requestUri;
		std::unordered_map<std::string, std::string> headers;
		std::unordered_map<std::string, std::string> get;

		std::string toString() const;
	};

	inline std::string RequestData::toString() const {
		std::string methodStr;
		switch (method) {
			case GET: methodStr += "GET"; break;
			case POST: methodStr += "POST"; break;
			case PUT: methodStr += "PUT"; break;
			case DELETE: methodStr += "DELETE"; break;
		}

		return methodStr + " " + requestUri;
	}
}

#endif