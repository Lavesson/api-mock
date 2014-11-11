#include "actioncontroller.h"

ApiMock::ActionController::ActionController(RequestAction getAction)
	: _getAction(getAction) {}

ApiMock::ResponseData ApiMock::ActionController::get(RequestData request) {
	return _getAction(this, request);
}