#include "t-unit.h"
#include "api-mock.h"
#include <http/mimetypes.h>

using ApiMock::Mime;

FIXTURE(MimeTests) {
	TEST(GetActualMimeBasedOnExtension) {
		assert.are_equal("application/javascript", Mime::GetMimeByFileName("myscript.js").mimeType);
	}

	TEST(ReturnPlainTextOnMissingExtension) {
		assert.are_equal("text/plain", Mime::GetMimeByFileName("hello.ohnoesthisisnotworking").mimeType);
	}

	TEST(NoExtensionReturnsTextPlain) {
		assert.are_equal("text/plain", Mime::GetMimeByFileName("thisisafilename").mimeType);
	}

	TEST(CaseDoesNotMatter) {
		assert.are_equal("text/css", Mime::GetMimeByFileName("test.CSS").mimeType);
	}

	TEST(ShouldNotCatchDotsFurtherBack) {
		assert.are_equal("text/plain", Mime::GetMimeByFileName("Test.css\\myfile").mimeType);
	}
}