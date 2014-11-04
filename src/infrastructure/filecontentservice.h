#ifndef	APIMOCK_FILECONTENTSERVICE_H
#define APIMOCK_FILECONTENTSERVICE_H

#include "contentservice.h"

namespace ApiMock {
	class FileContentService : public ContentService {
	public:
		Content getContent(std::string const& path) override;
	};
}

#endif