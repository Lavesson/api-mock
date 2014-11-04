#ifndef	APIMOCK_MIMETYPES_H
#define APIMOCK_MIMETYPES_H

#include <unordered_map>

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

			std::string::size_type idx;
			idx = filename.rfind('.');

			if (idx != std::string::npos)
				return MIME_TYPES.at(filename.substr(idx + 1));

			// If unknown, default to text/plain
			return "text/plain";
		}
	};
}

#endif