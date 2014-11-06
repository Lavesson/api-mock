#ifndef	APIMOCK_MIMETYPES_H
#define APIMOCK_MIMETYPES_H

#include <unordered_map>
#include <regex>

namespace ApiMock {
	class Mime {

	public:
		static std::string GetMimeByFileName(const std::string& filename) {
			static const std::unordered_map<std::string, std::string> MIME_TYPES{
					{ "css", "text/css" },
					{ "html", "text/html" },
					{ "js", "application/javascript" },
					{ "jpg", "image/jpeg" },
					{ "jpeg", "image/jpeg" },
					{ "png", "image/png" },
			};

			std::string fnLowerCase;
			std::transform(filename.begin(), filename.end(), std::back_inserter(fnLowerCase), ::tolower);
			std::smatch ext;
			const std::string DEFAULT = "text/plain";

			return std::regex_search(fnLowerCase, ext, std::regex("\\.(\\w+)$"))
				? (MIME_TYPES.find(ext[1]) != MIME_TYPES.end() ? MIME_TYPES.at(ext[1]) : DEFAULT) 
				: DEFAULT;
		}
	};
}

#endif