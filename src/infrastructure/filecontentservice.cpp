#include "filecontentservice.h"
#include "http/mimetypes.h"
#include <fstream>

ApiMock::Content ApiMock::FileContentService::getContent(const std::string& path) {
	Content content;

	std::ifstream dashboard("www/dashboard.html");
	std::string temp;
	std::string body;

	while (std::getline(dashboard, temp))
		body += temp;

	Content c;

	c.content = body;
	c.mimeType = "text/html";

	return c;
}