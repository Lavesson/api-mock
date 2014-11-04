#ifndef	APIMOCK_MIMETYPES_H
#define APIMOCK_MIMETYPES_H

#include <unordered_map>

namespace ApiMock {
	class Mime {

	public:
		std::string GetMimeByFileName(const std::string& filename) {
			static const std::unordered_map<std::string, std::string> MIME_TYPES{
					{ ".css", "text/css" },
					{ ".html", "text/html" },
					{ ".js", "application/javascript" },
					{ ".jpg", "image/jpeg" },
					{ ".jpeg", "image/jpeg" },
					{ ".png", "image/png" },
			};

			// TODO: Uh. Implement
			return "";
		}
	};
}

#endif