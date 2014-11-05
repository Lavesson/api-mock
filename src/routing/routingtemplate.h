#ifndef	APIMOCK_ROUTINGTEMPLATE_H
#define APIMOCK_ROUTINGTEMPLATE_H

#include <string>
#include <vector>

namespace ApiMock {
	class RoutingTemplate {
		std::string _routeTemplate;
		std::vector<std::string> _routeParts;
		std::vector<std::string> splitUriIntoParts(const std::string& uri) const;
		bool numberOfArgsNotMatching(const std::vector<std::string>& uriParts) const;
		bool isTemplatePart(const std::string& uriPart) const;
		bool constraintsNotMatching(const std::vector<std::string>& uriParts) const;

	public:
		bool operator==(const RoutingTemplate& other) const;
		explicit RoutingTemplate(const std::string& routeTemplate);
		std::string getTemplate() const;
		bool isMatch(const std::string& uri) const;
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