#include <iostream>
#include <unordered_map>

typedef std::unordered_map<std::string, std::string> Flags;
typedef std::pair<std::string, std::string> FlagEntry;

static const int FLAG_SIGN_LENGTH = 2;
static const std::string FLAG_SIGN = "--";

FlagEntry extractFlagEntry(const std::string& entry) {
	const std::string DELIMITER = "=";
	auto delimiterIndex = entry.find(DELIMITER);

	return (delimiterIndex == std::string::npos)
		? std::make_pair(entry, "")
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

int main(int argc, char** argv) {
	std::cout << "Starting server" << std::endl;

	auto flags = parseFlags(argc, argv);

	return 0;
}