#include "result.h"

ApiMock::Html::Html(std::string const& html) 
	: _html(html) {}

std::string ApiMock::Html::getMimeType() {
	return "text/html";
}

std::string ApiMock::Html::getSerializedResult() {
	return _html;
}