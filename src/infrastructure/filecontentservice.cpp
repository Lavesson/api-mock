#include "filecontentservice.h"
#include "http/mimetypes.h"
#include "infrastructure/exceptions.h"
#include <fstream>

ApiMock::Content ApiMock::FileContentService::getContent(const std::string& path) {
	Content content;
	auto dashFile = path;
	std::ifstream dashboard(dashFile);

	if (!dashboard.is_open()) throw FileNotFoundException(path);

	std::string temp;
	std::string body;

	while (std::getline(dashboard, temp))
		body += temp;

	dashboard.close();
	Content c;

	c.content = body;
	c.mimeType = Mime::GetMimeByFileName(dashFile);

	return c;
}