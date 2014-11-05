#ifndef T_UNIT_CONSOLE_COLOURS_H
#define T_UNIT_CONSOLE_COLOURS_H

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <iostream>
#endif

enum class colour {
	white,
	standard,
	red,
	green,
	yellow,
};

class console_colours
{
private:
	bool _use;
#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO _csbi;
	HANDLE _out;
#endif

public:
	console_colours(bool use) : _use(use) {
#ifdef _WIN32
		_out = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(_out, &_csbi);
#endif
	}

	void set_colour(colour c) {
		if (!_use) return;

#ifdef _WIN32
		switch (c)
		{
		case colour::white: SetConsoleTextAttribute(_out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); break;
		case colour::standard: SetConsoleTextAttribute(_out, _csbi.wAttributes); break;
		case colour::red: SetConsoleTextAttribute(_out, FOREGROUND_RED); break;
		case colour::green: SetConsoleTextAttribute(_out, FOREGROUND_GREEN); break;
		case colour::yellow: SetConsoleTextAttribute(_out, FOREGROUND_RED | FOREGROUND_GREEN); break;
		default: break;
		}
#else
		switch (c)
		{
		case colour::white: std::cout << "\033[1;37m"; break;
		case colour::standard: std::cout << "\033[0m"; break;
		case colour::red: std::cout << "\033[0;31m"; break;
		case colour::green: std::cout << "\033[0;32m"; break;
		case colour::yellow: std::cout << "\033[0;33m"; break;
		default: break;
		}
#endif
	}
};

#endif
