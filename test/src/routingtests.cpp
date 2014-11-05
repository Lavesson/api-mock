#include "t-unit.h"
#include "api-mock.h"

FIXTURE(RoutingTests) {
	TEST(MatchesNonTemplatedRoute) {
		ApiMock::RoutingTemplate sut("/first/second");
		assert.is_true(sut.isMatch("/first/second"));
	}

	TEST(MatchesTemplatedRoute) {
		ApiMock::RoutingTemplate sut("/first/{second}/third");
		assert.is_true(sut.isMatch("/first/banana/third"));
	}

	TEST(GetsCorrectTemplateValues) {
		ApiMock::RequestData request;
		request.requestUri = "/first/banana/third";
		ApiMock::RouteDictionary::Inject("/first/{second}/third", &request);
		assert.are_equal("banana", request.get["second"]);
	}
}