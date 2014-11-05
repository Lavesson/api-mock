#ifndef T_UNIT_HTML_REPORT_H
#define T_UNIT_HTML_REPORT_H

#include "t-unit.h"
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include <iostream>

std::ostream& operator<<(std::ostream& os, const test_result& test);
std::ostream& operator<<(std::ostream& os, const test_harness& harness);
std::ostream& operator<<(std::ostream& os, const test_fixture& fixture);

class html_report : public report_generator
{
private:
	const std::string report_file;

public:
	friend std::ostream& operator<<(std::ostream& os, const test_result& test);
	friend std::ostream& operator<<(std::ostream& os, const test_harness& harness);
	friend std::ostream& operator<<(std::ostream& os, const test_fixture& fixture);

	void generate_for(const test_harness& harness) {
		std::fstream file(report_file.c_str(), std::fstream::out);
		file << harness;
		file.flush();
		file.close();
	}

	explicit html_report(const std::string& report_file)
		: report_file(report_file) {}
};

std::ostream& operator<<(std::ostream& os, const test_harness& harness) {
	// DTD+head
	os << "<!doctype html>" << "<html lang=\"en\">";
	os << "<head><title>Test Report [t-unit]</title>";
	os << "<link rel=\"stylesheet\" href=\"report.css\">";
	os << "<script src=\"details-shim.js\"></script></head>";

	// Body
	os << "<body><code>";

	// Test harness header
	os << "<details open=\"open\" id=\"header\">";
	os << "<summary>Test Report [" << harness.t_unit_version() << "]</summary>";
	os << "<div class=\"diagnostics\">";
	os << "<div>" << harness.num_total_tests() << " tests in " << harness.num_fixtures() <<" fixtures. Ran in " << harness.duration_ms() << " ms.</div>";
	os << "<div class=\"passed\">" << harness.num_passed_tests() << " passed</div>";
	os << "<div class=\"failed\">" << harness.num_failed_tests() << " failed</div>";
	os << "<div class=\"inconclusive\">" << harness.num_inconclusive_tests() << " inconclusive</div>";
	os << "<div class=\"skipped\">" << harness.num_skipped_tests() << " skipped</div>";
	os << "</div>";
	os << "</details>";

	// stream fixtures
	for (auto f : harness.fixtures())
		os << *f;

	os << "</code></body>";
	os << "</html>";

	return os;
}

std::ostream& operator<<(std::ostream& os, const test_fixture& fixture) {
	bool none_failed = fixture.failed_test_count() == 0;
	std::string fixture_class = (none_failed ? "passed" : "failed");
	std::string details_attribute = (none_failed ? "" : " open=\"open\"");
	int dur = fixture.total_duration_ms();

	os << "<div class=\"fixture\"><details" << details_attribute << ">";
	os << "<summary>" << fixture.name << " - <span class=\"" << fixture_class << "\">"
	   << (none_failed ? "Passed" : "Failed") << " [" << (dur == 0 ? "<1" : std::to_string(dur))
	   << " ms]" << "</span>" << "</summary>";
	os << "<div class=\"test-collection\">";

	for (auto result : fixture.results)
		os << result;

	os << "</div>";
	os << "</details>";
	os << "</div>";

	return os;
}

std::ostream& operator<<(std::ostream& os, const test_result& test) {
	std::string case_class; std::string case_text;
	std::string details_attribute = (test.ok ? "" : " open=\"open\"");
	os << "<details class=\"test\"" << details_attribute << ">";
	int dur = test.duration_ms;

	switch (test.status) {
	case test_status::ok:			case_class = "passed"; case_text = "Passed [" + (dur == 0 ? "<1" : std::to_string(dur)) + " ms]"; break;
	case test_status::not_ok:		case_class = "failed"; case_text = "Failed [" + (dur == 0 ? "<1" : std::to_string(dur)) + " ms]"; break;
	case test_status::skipped:		case_class = "skipped"; case_text = "Skipped"; break;
	case test_status::inconclusive:	case_class = "inconclusive"; case_text = "Inconclusive"; break;
	default:						case_class = "[unknown]"; case_text = "[unknown]"; break;
	}

	os << "<summary>" << test.test_label << " - <span class=\"" << case_class << "\">" << case_text << "</span></summary>";

	if (test.status == test_status::not_ok) {
		auto d = test.diagnostics;
		os << "<div class=\"diagnostics " << case_class << "\"><br>";
		os << "# got: " << d.actual << "<br>";
		os << "# expected: " << d.expected << "<br>";
		if (d.comment != "") os << "# " << d.comment << "<br>";
		os << "</div>";
	}

	os << "</details>";
	return os;
}

#endif
