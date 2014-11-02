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


	class Html : public Result {
		std::string _html;

	public:
		Html(const std::string& html);
		std::string getMimeType() override;
		std::string getSerializedResult() override;
	};
}

#endif