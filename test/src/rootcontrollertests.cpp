#include "t-unit.h"
#include "api-mock.h"
#include <memory.h>
#include "mocks/contentstub.h"
#include "http/statuscodes.h"
#include "controllers/rootcontroller.h"

using ApiMock::RootController;
using ApiMock::Content;
using ApiMock::RequestData;
using ApiMock::ResponseData;

FIXTURE(RootControllerTests) {
	std::unique_ptr<RootController> sut;
	std::unique_ptr<ContentStub> contentStub;

	SETUP() {
		contentStub = std::unique_ptr<ContentStub>(
			new ContentStub);

		sut = std::unique_ptr<RootController>(
			new RootController(contentStub.get()));
	}

	TEST(GetContentFromService) {
		RequestData request; request.get["@wildcard"] = "temp.html";
		sut->get(request);
		assert.are_equal(1, contentStub->getContentTimesCalled);
		assert.are_equal("www/app/temp.html", contentStub->lastPath);
	}

	TEST(StatusOkWhenResourceFound) {
		RequestData request; request.get["@wildcard"] = "temp.html";
		Content c;
		c.content = "test"; c.mimeType = "text/bananas";
		contentStub->getContentValue = c;
		auto response = sut->get(request);

		assert.are_equal(ApiMock::HTTP_OK, response.statusCode);
	}

	TEST(StatusNotFoundWhenNoResource) {
		contentStub->_getContent = [](const std::string& s) -> Content {
			throw ApiMock::FileNotFoundException(s);
		};

		RequestData request; request.get["@wildcard"] = "temp.html";
		auto response = sut->get(request);
		assert.are_equal(ApiMock::HTTP_NOT_FOUND, response.statusCode);
	}

	TEST(StatusNotFoundWhenWildcardArgMissing) {
		RequestData request;
		auto response = sut->get(request);
		assert.are_equal(ApiMock::HTTP_NOT_FOUND, response.statusCode);
	}
}