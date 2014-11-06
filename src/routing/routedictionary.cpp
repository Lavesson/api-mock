#include "routedictionary.h"
#include "http/requestdata.h"
#include <sstream>
#include <algorithm>
#include <vector>
#include <regex>

using std::vector;
using std::string;
using std::stringstream;
using std::regex;

/* 
 * TODO: I get the feeling that I have the wrong structure here. Basically, I'm reusing functions from 
 * ApiMock::RoutingTemplate. On the other hand, the injection should probably not be done in that class
 * either. I'm suspecting that a helper class or some free helper functions might be in order instead...
 */

vector<string> splitUriIntoParts(const string& uri) {
	vector<string> output;
	stringstream ss(uri);
	string next;

	while (std::getline(ss, next, '/')) {
		if (next != "") output.push_back(next);
	}

	return output;
}

bool isTemplatePart(string templatePart) {
	return (
		std::regex_match(templatePart, regex("\\{\\w+\\}")));
}


bool isWildcard(const std::string& templatePart) {
	return templatePart == "*";
}

string templateName(string templatePart) {
	std::smatch matches;
	std::regex_match(templatePart, matches, regex("\\{(\\w+)\\}"));
	return matches[1];
}

void ApiMock::RouteDictionary::Inject(std::string routeTemplate, RequestData* request) {
	auto templateUriParts = splitUriIntoParts(routeTemplate);
	auto incomingUriParts = splitUriIntoParts(request->requestUri);

	for (unsigned i = 0; i < templateUriParts.size(); ++i) {
		if (isTemplatePart(templateUriParts[i])) {
			request->get.insert(
				std::make_pair(templateName(templateUriParts[i]), incomingUriParts[i]));
		} else if (isWildcard(templateUriParts[i])) {
			string joined;

			std::for_each(incomingUriParts.begin() + i, incomingUriParts.end(), [&joined](string item) {
				joined += item + "/";
			});

			// Remove the last trailing '/' from the foreach
			joined.pop_back();

			request->get.insert(
				std::make_pair("@wildcard", joined));
		}
	}
}