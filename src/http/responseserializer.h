#ifndef APIMOCK_RESPONSESERIALIZER_H
#define APIMOCK_RESPONSESERIALIZER_H
#include <string>

namespace ApiMock {
	struct ResponseData;

	class ResponseSerializer {
	public:
		std::string serialize(ResponseData response_data);
	};
}

#endif