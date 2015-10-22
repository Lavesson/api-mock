#include "controllers/controller.h"
#include <infrastructure/contentservice.h>

namespace ApiMock {
	class RootController : public Controller {
	private:
		ContentService* _content;

	public:
		explicit RootController(ContentService* content);
		ResponseData get(RequestData request) override;
	};
}
