#include "t-unit.h"
#include <routing/routingtemplate.h>

FIXTURE(RoutingTests) {
	TEST(MatchesNonTemplatedRoute) {
		ApiMock::RoutingTemplate sut("/first/second");
		assert.is_true(sut.isMatch("/first/second"));
	}

	TEST(MatchesTemplatedRoute) {
		ApiMock::RoutingTemplate sut("/first/{second}/third");
		assert.is_true(sut.isMatch("/first/banana/third"));
	}
}