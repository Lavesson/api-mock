#pragma once
#include "contentservice.h"
#include <string>

namespace ApiMock {
	class FileContentService : public ContentService {
		std::string getBinaryContent(const std::string& path);
		std::string getTextualContent(const std::string& path);

	public:
		Content getContent(std::string const& path) override;
	};
}
