#include <iostream>
#include <unordered_map>
#include "api-mock.h"

typedef std::unordered_map<std::string, std::string> Flags;
typedef std::pair<std::string, std::string> FlagEntry;

static const std::string ADDRESS = "127.0.0.1";
static const int FLAG_SIGN_LENGTH = 2;
static const std::string FLAG_SIGN = "--";
static const Flags DEFAULT_OPTIONS = {
		{ "port", "8888" },
		{ "buffer", "8192" }
};

FlagEntry extractFlagEntry(const std::string& entry) {
	const std::string DELIMITER = "=";
	auto delimiterIndex = entry.find(DELIMITER);

	return (delimiterIndex == std::string::npos)
		? std::make_pair(entry.substr(FLAG_SIGN_LENGTH, delimiterIndex - FLAG_SIGN_LENGTH), "")
		: std::make_pair(entry.substr(FLAG_SIGN_LENGTH, delimiterIndex-FLAG_SIGN_LENGTH), entry.substr(delimiterIndex + 1));
}

Flags parseFlags(int argc, char** argv) {
	Flags f;

	for (int i = 1; i < argc; ++i) {
		auto next = std::string(argv[i]);

		if (next.length() > FLAG_SIGN_LENGTH && next.substr(0, FLAG_SIGN_LENGTH) == FLAG_SIGN)
			f.insert(extractFlagEntry(argv[i]));
	}

	return f;
}

Flags getMergedFlags(int argc, char** argv) {
	auto flagsFromCmdLine = parseFlags(argc, argv);
	flagsFromCmdLine.insert(DEFAULT_OPTIONS.begin(), DEFAULT_OPTIONS.end());
	return flagsFromCmdLine;
}

void startServer(Flags flags) {
	try {
		ApiMock::HttpServer s;
		ApiMock::RoutedResourceStrategy routes;
		ApiMock::ConfigureDependencies();
		ApiMock::ConfigureRoutes(&routes);
		
		s.startServer(
			ADDRESS, std::stoi(flags["port"]), std::stoi(flags["buffer"]), &routes);
	}
	catch (ApiMock::SocketException e) {
		printf("%s\n", e.what());
	}
}

int main(int argc, char** argv) {
	auto flags = getMergedFlags(argc, argv);
	printf("Starting server at %s:%s\n", ADDRESS.c_str(), flags["port"].c_str());
	startServer(flags);
	return 0;
}