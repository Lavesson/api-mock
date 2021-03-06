#pragma once
#include "controller.h"

namespace ApiMock {
	class ContentService;

	class DashboardController : public Controller {
	private:
		ContentService* _content;

	public:
		DashboardController(ContentService* content);
		ResponseData get(RequestData request) override;
	};
}
