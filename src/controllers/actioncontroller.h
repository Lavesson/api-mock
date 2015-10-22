#pragma once
#include "controller.h"
#include <functional>

namespace ApiMock {
	class ActionController : public Controller {
		typedef std::function<ResponseData(Controller*, const RequestData&)> RequestAction;
		RequestAction _getAction;

	public:
		explicit ActionController(RequestAction getAction);
		ResponseData get(RequestData request) override;
	};
}
