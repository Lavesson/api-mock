#pragma once
#include <string>
#include <unordered_map>

namespace ApiMock {
	struct RequestData;

	struct RouteDictionary {
		static void Inject(std::string routeTemplate, RequestData* request);
		std::unordered_map<std::string, std::string> get;
	};
}
