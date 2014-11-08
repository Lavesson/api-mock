#include "contentstub.h"

ContentStub::ContentStub() {
	_getContent = [&](const std::string path)
	{
		lastPath = path;
		getContentTimesCalled++;
		return getContentValue;
	};
}

ApiMock::Content ContentStub::getContent(std::string const& path) {
	return _getContent(path);
}