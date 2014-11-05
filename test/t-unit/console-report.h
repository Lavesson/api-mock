#ifndef T_UNIT_CONSOLE_REPORT_H
#define T_UNIT_CONSOLE_REPORT_H

#include "t-unit.h"
#include "console-colours.h"
#include <iostream>

class console_report : public report_generator
{
	void generate_for(const test_harness& harness)
	{
		console_colours col(true); // TODO: pass bool in some nicer way :(
		std::cout << "# " << harness.t_unit_version() << std::endl << "#" << std::endl;

		if (!harness.num_failed_tests()) {
			std::cout << "# "; col.set_colour(colour::green);
			std::cout << "All tests passed"; ; col.set_colour(colour::standard);
			std::cout << std::endl << "#" << std::endl;
		}

		for (auto f : harness.fixtures()) {
			for (auto t : f->results) {
				if (t.status == test_status::not_ok) {
					std::cout << "# "; col.set_colour(colour::red); std::cout << "FAILED: [" << t.test_label << "] in fixture [" << f->name << "]"; col.set_colour(colour::standard); 
					std::cout << std::endl;
					std::cout << "# "; col.set_colour(colour::red); std::cout << "   got:      " << t.diagnostics.actual; col.set_colour(colour::standard); 
					std::cout << std::endl;
					std::cout << "# "; col.set_colour(colour::red); std::cout << "   expected: " << t.diagnostics.expected; col.set_colour(colour::standard);
					std::cout << std::endl;
					if (t.diagnostics.comment != "") {
						std::cout << "#    "; col.set_colour(colour::red); std::cout << t.diagnostics.comment; col.set_colour(colour::standard); 
						std::cout << std::endl;
					}
					std::cout << "#" << std::endl;
				}
			}
		}

		std::cout 
				<< "# " << harness.num_total_tests() << " tests in " << harness.num_fixtures() << " fixture(s). Ran in " 
				<< harness.duration_ms() << " ms" << std::endl;
			std::cout  << "# ";
			
			col.set_colour(colour::green);	  std::cout << harness.num_passed_tests() << " passed. ";
			col.set_colour(colour::red);	  std::cout << harness.num_failed_tests() << " failed. ";
			col.set_colour(colour::yellow);   std::cout << harness.num_inconclusive_tests() << " inconclusive. ";
			col.set_colour(colour::white);	  std::cout << harness.num_skipped_tests() << " skipped";
			col.set_colour(colour::standard); std::cout << std::endl;
	}
};

#endif
