#pragma once
#include <string>

namespace ApiMock {
	struct Content {
		std::string content;
		std::string mimeType;
	};

	class ContentService {
	public:
		virtual ~ContentService() {}
		virtual Content getContent(const std::string& path) = 0;
	};
}
