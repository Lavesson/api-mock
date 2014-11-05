#include "filecontentservice.h"
#include "http/mimetypes.h"
#include <fstream>

ApiMock::Content ApiMock::FileContentService::getContent(const std::string& path) {
	Content content;
	auto dashFile = path;
	std::ifstream dashboard(dashFile);
	std::string temp;
	std::string body;

	while (std::getline(dashboard, temp))
		body += temp;

	Content c;

	c.content = body;
	c.mimeType = Mime::GetMimeByFileName(dashFile);

	return c;
}