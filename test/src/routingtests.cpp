#include "t-unit.h"
#include "api-mock.h"

using ApiMock::RoutingTemplate;

FIXTURE(RoutingTests) {
	TEST(MatchesNonTemplatedRoute) {
		assert.is_true(RoutingTemplate("/first/second")
			.isMatch("/first/second"));
	}

	TEST(MatchesTemplatedRoute) {
		assert.is_true(RoutingTemplate("/first/{second}/third")
			.isMatch("/first/banana/third"));
	}

	TEST(GetsCorrectTemplateValues) {
		ApiMock::RequestData request;
		request.requestUri = "/first/banana/third";
		ApiMock::RouteDictionary::Inject("/first/{second}/third", &request);
		assert.are_equal("banana", request.get["second"]);
	}

	TEST(MatchesWildcard) {
		assert.is_true(RoutingTemplate("/first/second/*")
			.isMatch("/first/second/third/fourth"));
	}

	TEST(TooFewArgsOnWildcardedRouteDoesNotMatch) {
		assert.is_false(RoutingTemplate("/first/second/*")
			.isMatch("/first"));
	}
}