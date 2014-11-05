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
	: _routeTemplate(routeTemplate), _routeParts(splitUriIntoParts(routeTemplate)) {}

string ApiMock::RoutingTemplate::getTemplate() const {
	return _routeTemplate;
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

bool ApiMock::RoutingTemplate::numberOfArgsNotMatching(const std::vector<std::string>& uriParts) const {
	return (uriParts.size() != _routeParts.size());
}

bool ApiMock::RoutingTemplate::isTemplatePart(std::string const& uriPart) const {
		return (
			std::regex_match(uriPart, regex("\\{\\w+\\}")));
}

bool ApiMock::RoutingTemplate::constraintsNotMatching(const std::vector<std::string>& uriParts) const {
	for (auto i = 0; i < uriParts.size(); ++i) {
		if (!isTemplatePart(_routeParts[i])) {
			if (uriParts[i] != _routeParts[i])
				return true;
		}
	}

	return false;
}

bool ApiMock::RoutingTemplate::isMatch(string const& uri) const {
	// TODO: Right now, I'm just matching exact URLs, which sucks.
	vector<string> uriParts = splitUriIntoParts(uri);

	if (numberOfArgsNotMatching(uriParts) || constraintsNotMatching(uriParts))
		return false;

	return true;

	//return (uri == _routeTemplate);
}