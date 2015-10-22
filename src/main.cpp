#include <iostream>
#include <unordered_map>
#include <algorithm>
#include "api-mock.h"

typedef std::unordered_map<std::string, std::string> Flags;
typedef std::pair<std::string, std::string> FlagEntry;

static const std::string ADDRESS = "127.0.0.1";
static const int FLAG_SIGN_LENGTH = 2;
static const std::string FLAG_SIGN = "--";
static const Flags DEFAULT_OPTIONS = {
		{ "port", "8888" },
		{ "buffer", "8192" },
};

static const std::vector<std::string> SUPPORTED_FLAGS = {
		"port", "buffer", "help", "verbose"
};

bool supportedFlag(const std::string& flag) {
	return std::find(SUPPORTED_FLAGS.begin(), SUPPORTED_FLAGS.end(), flag) != SUPPORTED_FLAGS.end();
}

void makeSureFlagIsSupported(const std::string& entry) {
	if (!supportedFlag(entry))
		throw ApiMock::UnknownFlagException(entry);
}

FlagEntry extractFlagEntry(const std::string& entry) {
	const std::string DELIMITER = "=";
	auto delimiterIndex = entry.find(DELIMITER);

	FlagEntry flag = (delimiterIndex == std::string::npos)
					 ? std::make_pair(entry.substr(FLAG_SIGN_LENGTH, delimiterIndex - FLAG_SIGN_LENGTH), "")
					 : std::make_pair(entry.substr(FLAG_SIGN_LENGTH, delimiterIndex-FLAG_SIGN_LENGTH),
									  entry.substr(delimiterIndex + 1));

	makeSureFlagIsSupported(flag.first);
	return flag;
}

bool isValidFlagFormat(const std::string &next) {
	return next.length() > FLAG_SIGN_LENGTH && next.substr(0, FLAG_SIGN_LENGTH) == FLAG_SIGN;
}

Flags parseFlags(int argc, char** argv) {
	Flags f;

	for (int i = 1; i < argc; ++i) {
		auto next = std::string(argv[i]);

		if (isValidFlagFormat(next))
			f.insert(extractFlagEntry(argv[i]));
	}

	return f;
}

Flags getMergedFlags(int argc, char** argv) {
	auto flagsFromCmdLine = parseFlags(argc, argv);
	flagsFromCmdLine.insert(DEFAULT_OPTIONS.begin(), DEFAULT_OPTIONS.end());
	return flagsFromCmdLine;
}

bool flagIsPresent(std::string flag, Flags flags) {
	return flags.find(flag) != flags.end();
}

void startServer(Flags flags) {
	try {
		ApiMock::HttpServer s(flagIsPresent("verbose", flags));
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

void showUsage() {
	printf(
		"Usage: api-mock [options]\n"
		"\n"
		"Options:\n"
		"  --port=PORT          Set the port to use when starting the server.\n"
		"                       Default port value is 8888.\n"
		"  --buffer=BYTES       Set the size in bytes of the buffer used for\n"
		"                       HTTP requests. Default size is 8192 bytes\n"
		"  --help               Print this screen.\n"
		"  --verbose            Log all output to the terminal.\n"
		"\n");
}

int main(int argc, char** argv) {
	try {
		auto flags = getMergedFlags(argc, argv);

		if (flagIsPresent("help", flags)) {
			showUsage();
			return 0;
		}

		printf("Starting server at %s:%s\n", ADDRESS.c_str(), flags["port"].c_str());
		startServer(flags);
		return 0;
	} catch (ApiMock::UnknownFlagException e) {
		printf("%s\n", e.what());
	}
}