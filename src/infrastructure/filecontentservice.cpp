#include "filecontentservice.h"
#include "http/mimetypes.h"
#include "infrastructure/exceptions.h"
#include <fstream>
#include <algorithm>

using std::string;
using std::ifstream;
using std::ios;
using std::vector;
using std::for_each;

string ApiMock::FileContentService::getBinaryContent(const string& path) {
	ifstream handle(path, ios::binary | ios::ate);

	if (!handle.is_open())
		throw FileNotFoundException(path);

	ifstream::pos_type pos = handle.tellg();
	vector<char> result(pos);

	handle.seekg(0, std::ios::beg);
	handle.read(&result[0], pos);

	string body = "";

	for_each(result.begin(), result.end(), [&body](char next)
	{
		body.push_back(next);
	});

	return body;
}

string ApiMock::FileContentService::getTextualContent(const string& path) {
	Content content;
	std::ifstream handle(path);

	if (!handle.is_open()) 
		throw FileNotFoundException(path);

	string temp;
	string body;

	while (std::getline(handle, temp))
		body += (temp + '\n');

	handle.close();
	return body;
}

ApiMock::Content ApiMock::FileContentService::getContent(const std::string& path) {
	auto mime = Mime::GetMimeByFileName(path);

	string body = (mime.mode == BINARY)
		? getBinaryContent(path)
		: getTextualContent(path);

	Content c;

	c.content = body;
	c.mimeType = mime.mimeType;

	return c;
}