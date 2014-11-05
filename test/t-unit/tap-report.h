#ifndef T_UNIT_TAP_REPORT_H
#define T_UNIT_TAP_REPORT_H

#include "t-unit.h"
#include <iostream>

class tap_report : public report_generator
{
private:
	std::ostream& _s;

public:
	explicit tap_report(std::ostream& stream=std::cout) : _s(stream) {}

	virtual void generate_for(const test_harness& harness) {
		_s << "1.." << harness.num_total_tests() << std::endl;
		
		int offset = 0;

		for (auto f : harness.fixtures()) {
			for (auto t : f->results) {
				if (t.status == test_status::inconclusive) // Could perhaps be done in a nicer manner
					_s << "not ok " << (t.id+1+offset) << " - " << t.test_label << " # TODO Test not implemented yet" << std::endl;
				else
					_s << (t.ok ? "ok " : "not ok ") << (t.id+1+offset) << " - " << t.test_label << (t.skipped ? " # SKIP" : "") << std::endl;

				if (!t.ok) {
					auto d = t.diagnostics;
					_s << "# got: " << d.actual << std::endl;
					_s << "# expected: " << d.expected << std::endl;
					if (d.comment != "") _s << "# " << d.comment << std::endl;
				}
			}
			offset += f->test_count();
		}
	}
};

#endif