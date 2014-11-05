#include "routingtemplate.h"
#include <vector>
#include <sstream>
#include <regex>

using std::vector;
using std::string;
using std::stringstream;
using std::regex;

bool ApiMock::RoutingTemplate::operator==(const RoutingTemplate& other) const {
	return (other._routeTemplate == _routeTemplate);
}

ApiMock::RoutingTemplate::RoutingTemplate(const string& routeTemplate)
	: _routeTemplate(routeTemplate) {}

string ApiMock::RoutingTemplate::getTemplate() const {
	return _routeTemplate;
}

bool ApiMock::RoutingTemplate::matchesArgsToWildcard(std::string const& uri) const {
	/* Grab the part or the template before the wildcard */
	auto subrouteParts = splitUriIntoParts(_routeTemplate.substr(0, _routeTemplate.find("/*")));	
	auto uriParts = splitUriIntoParts(uri);

	vector<string> reducedUriParts;
	std::copy(
		uriParts.begin(),
		uriParts.begin() + std::min(subrouteParts.size(), uriParts.size()),
		std::back_inserter(reducedUriParts));

	return matchingArgsAndConstraints(reducedUriParts, subrouteParts);
}

bool ApiMock::RoutingTemplate::matchesAllArgs(std::string const& uri) const {
	auto uriParts = splitUriIntoParts(uri);
	auto routeParts = splitUriIntoParts(_routeTemplate);
	return matchingArgsAndConstraints(uriParts, routeParts);
}

bool ApiMock::RoutingTemplate::wildcardedRoute() const {
	return _routeTemplate.find("/*") != std::string::npos;
}

vector<string> ApiMock::RoutingTemplate::splitUriIntoParts(const string& uri) const {
	vector<string> output;
	stringstream ss(uri);
	string next;

	while (std::getline(ss, next, '/')) {
		if (next != "") output.push_back(next);
	}

	return output;
}

bool ApiMock::RoutingTemplate::numberOfArgsNotMatching(const vector<string>& uriParts, const vector<string>& routeParts) const {
	return (uriParts.size() != routeParts.size());
}

bool ApiMock::RoutingTemplate::isTemplatePart(std::string const& uriPart) const {
		return (
			std::regex_match(uriPart, regex("\\{\\w+\\}")));
}

bool ApiMock::RoutingTemplate::constraintsNotMatching(const std::vector<std::string>& uriParts, const vector<string>& routeParts) const {
	for (unsigned i = 0; i < uriParts.size(); ++i) {
		if (!isTemplatePart(routeParts[i])) {
			if (uriParts[i] != routeParts[i])
				return true;
		}
	}

	return false;
}

bool ApiMock::RoutingTemplate::matchingArgsAndConstraints(std::vector<std::string> const& uriParts, std::vector<std::string> const& routeParts) const {
	return !(numberOfArgsNotMatching(uriParts, routeParts) || constraintsNotMatching(uriParts, routeParts));
}

bool ApiMock::RoutingTemplate::isMatch(string const& uri) const {
	return wildcardedRoute()
		? matchesArgsToWildcard(uri)
		: matchesAllArgs(uri);
}