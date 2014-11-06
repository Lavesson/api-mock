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

	TEST(WildcardGetsMappedInDictionary) {
		ApiMock::RequestData request;
		request.requestUri = "/first/second/third/fourth";
		ApiMock::RouteDictionary::Inject("/first/second/*", &request);
		assert.are_equal("third/fourth", request.get["@wildcard"]);
	}

	TEST(CanCombineTemplatesAndWildcards) {
		ApiMock::RequestData request;
		request.requestUri = "/first/second/third/fourth";
		ApiMock::RouteDictionary::Inject("/first/{arg}/*", &request);
		assert.are_equal("third/fourth", request.get["@wildcard"]);
		assert.are_equal("second", request.get["arg"]);
	}
}