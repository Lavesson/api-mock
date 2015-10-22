#pragma once
#include <string>
#include <vector>

namespace ApiMock {
	class RoutingTemplate {
		std::string _routeTemplate;
		bool wildcardedRoute() const;
		std::vector<std::string> splitUriIntoParts(const std::string& uri) const;
		bool numberOfArgsNotMatching(const std::vector<std::string>& uriParts, const std::vector<std::string>& routeParts) const;
		bool constraintsNotMatching(const std::vector<std::string>& uriParts, const std::vector<std::string>& routeParts) const;
		bool matchingArgsAndConstraints(const std::vector<std::string>& uriParts, const std::vector<std::string>& routeParts) const;
		bool isTemplatePart(const std::string& uriPart) const;

	public:
		bool operator==(const RoutingTemplate& other) const;
		explicit RoutingTemplate(const std::string& routeTemplate);
		std::string getTemplate() const;
		bool matchesArgsToWildcard(const std::string& uri) const;
		bool matchesAllArgs(const std::string& uri) const;
		bool isMatch(const std::string& uri) const;
	};
}

namespace std {
	template <>
	struct hash<ApiMock::RoutingTemplate> {
		std::size_t operator()(const ApiMock::RoutingTemplate& key) const {
			return hash<std::string>()(key.getTemplate());
		}
	};
}
