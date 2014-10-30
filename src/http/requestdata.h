#ifndef APIMOCK_REQUESTDATA_H
#define APIMOCK_REQUESTDATA_H

#include <string>

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
	};
}

#endif