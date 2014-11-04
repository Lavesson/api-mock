#ifndef	APIMOCK_RESULT_H
#define APIMOCK_RESULT_H

#include <string>

namespace ApiMock {
	class Result {
	public:
		virtual ~Result() {}
		virtual std::string getSerializedResult() = 0;
		virtual std::string getMimeType() = 0;
	};


	class PureTextResult : public Result {
		std::string _payload;
		std::string _mime;

	public:
		PureTextResult(const std::string& payload, const std::string& mime);
		std::string getMimeType() override;
		std::string getSerializedResult() override;
	};
}

#endif