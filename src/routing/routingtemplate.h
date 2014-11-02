#ifndef	APIMOCK_ROUTINGTEMPLATE_H
#define APIMOCK_ROUTINGTEMPLATE_H

#include <string>

namespace ApiMock {
	class RoutingTemplate {
		std::string _routeTemplate;

	public:
		bool operator==(const RoutingTemplate& other) const;
		explicit RoutingTemplate(const std::string& routeTemplate);
		std::string getTemplate() const;
	};
}

namespace std {
	template <>
	struct hash<ApiMock::RoutingTemplate> {
		std::size_t operator()(const ApiMock::RoutingTemplate& key) {
			return hash<std::string>()(key.getTemplate());
		}
	};
}

#endif