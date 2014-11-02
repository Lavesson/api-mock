#ifndef	APIMOCK_DASHBOARDCONTROLLER_H
#define APIMOCK_DASHBOARDCONTROLLER_H

#include "controller.h"

namespace ApiMock {
	class DashboardController : public Controller {
	public:
		ResponseData get(RequestData request) override;
	};
}

#endif