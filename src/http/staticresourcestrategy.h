#include "resourcestrategy.h"

namespace ApiMock {
	class StaticResourceStrategy : public ResourceStrategy {
	public:
		ResponseData createResponse(RequestData const& request) override;
	};
}
