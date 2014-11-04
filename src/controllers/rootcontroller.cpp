#include "rootcontroller.h"

ApiMock::RootController::RootController(ContentService* content): _content(content) {

}

ApiMock::ResponseData ApiMock::RootController::get(RequestData request) {
	return createResponse(HTTP_OK);
}