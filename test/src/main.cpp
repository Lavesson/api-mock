#define PRETTY_COLOURS
#include <tap-report.h>
#include <console-report.h>

int main() {
	test_runner::run_all_tests();
	console_report cr;
	test_runner::create_report(cr);
	return 0;
}