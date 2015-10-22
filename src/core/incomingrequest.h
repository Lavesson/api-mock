#pragma once
#include <string>

namespace ApiMock {
	class IncomingRequest {
	public:
		virtual ~IncomingRequest() {}
		virtual std::string getRequestAsString() = 0;
		virtual void sendResponse(const std::string& responseAsString) = 0;
	};
}
