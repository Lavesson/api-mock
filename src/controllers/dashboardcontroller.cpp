#include "dashboardcontroller.h"
#include "serialization/result.h"
#include <fstream>

ApiMock::ResponseData ApiMock::DashboardController::get(RequestData request) {
	// TODO: This is temporary, just to try the concept out. But really: files shouldn't be loaded like this:
	std::ifstream dashboard("www/dashboard.html");
	std::string temp;
	std::string body;

	while (std::getline(dashboard, temp))
		body += temp;

	auto result = Html(body);
	return createResponse(HTTP_OK, &result);
}