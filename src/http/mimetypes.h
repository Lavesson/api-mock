#ifndef	APIMOCK_MIMETYPES_H
#define APIMOCK_MIMETYPES_H

#include <unordered_map>
#include <regex>

namespace ApiMock {
	enum FileMode {
		BINARY, TEXT /* I don't handle UTF8/16/Ascii differences right now. I should probably look into doing that */
	};

	struct MimeType {
		explicit MimeType(std::string const& mimeType, FileMode mode = TEXT)
			: mimeType(mimeType), mode(mode) {}

		std::string mimeType;
		FileMode mode;
	};

	class Mime {
	public:
		static MimeType GetMimeByFileName(const std::string& filename) {
			static const std::unordered_map<std::string, MimeType> MIME_TYPES{
					{ "css", MimeType("text/css") },
					{ "html", MimeType("text/html") },
					{ "js", MimeType("application/javascript") },
					{ "jpg", MimeType("image/jpeg", BINARY) },
					{ "jpeg", MimeType("image/jpeg", BINARY) },
					{ "png", MimeType("image/png", BINARY) },
					{ "woff", MimeType("application/font-woff", BINARY) },
			};

			std::string fnLowerCase;
			std::transform(filename.begin(), filename.end(), std::back_inserter(fnLowerCase), ::tolower);
			std::smatch ext;
			const MimeType DEFAULT("text/plain");

			return std::regex_search(fnLowerCase, ext, std::regex("\\.(\\w+)$"))
				? (MIME_TYPES.find(ext[1]) != MIME_TYPES.end() ? MIME_TYPES.at(ext[1]) : DEFAULT) 
				: DEFAULT;
		}
	};
}

#endif