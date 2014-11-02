#include "dashboardcontroller.h"
#include "serialization/result.h"

ApiMock::ResponseData ApiMock::DashboardController::get(RequestData request) {
	auto result = Html("<h1>Hello, world</h1>\n<p>This is an HTML result</p>");
	return createResponse(HTTP_OK, &result);
}