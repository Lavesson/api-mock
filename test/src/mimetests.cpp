#include "t-unit.h"
#include "api-mock.h"
#include <http/mimetypes.h>

using ApiMock::Mime;

FIXTURE(MimeTests) {
	TEST(GetActualMimeBasedOnExtension) {
		assert.are_equal("application/javascript", Mime::GetMimeByFileName("myscript.js"));
	}

	TEST(ReturnPlainTextOnMissingExtension) {
		assert.are_equal("text/plain", Mime::GetMimeByFileName("hello.ohnoesthisisnotworking"));
	}

	TEST(NoExtensionReturnsTextPlain) {
		assert.are_equal("text/plain", Mime::GetMimeByFileName("thisisafilename"));
	}

	TEST(CaseDoesNotMatter) {
		assert.are_equal("text/css", Mime::GetMimeByFileName("test.CSS"));
	}

	TEST(ShouldNotCatchDotsFurtherBack) {
		assert.are_equal("text/plain", Mime::GetMimeByFileName("Test.css\\myfile"));
	}
}