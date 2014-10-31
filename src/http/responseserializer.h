#ifndef APIMOCK_RESPONSESERIALIZER_H
#define APIMOCK_RESPONSESERIALIZER_H
#include <string>
#include <http/statuscodes.h>

namespace ApiMock {
	struct ResponseData;

	class ResponseSerializer {
	private:
		std::string statusCodeDescription(HTTP_RESPONSE_CODE responseCode);

	public:
		std::string serialize(ResponseData response_data);
	};
}

#endif