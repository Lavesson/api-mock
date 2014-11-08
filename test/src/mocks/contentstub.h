#ifndef TEST_CONTENTSTUB_H
#define	TEST_CONTENTSTUB_H
#include "infrastructure/contentservice.h"
#include <functional>

class ContentStub : public ApiMock::ContentService {
public:
	ContentStub();

	int getContentTimesCalled {0};
	ApiMock::Content getContentValue;
	std::string lastPath;
	
	ApiMock::Content getContent(std::string const& path) override;
	
	std::function<ApiMock::Content(std::string const& path)> _getContent;
};

#endif