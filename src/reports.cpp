#include "reports.h"
#include <iostream>

namespace badhron {

	CheckReport::CheckReport(const Prototype &proto) :
		function_{proto.function},
		subgroup_{proto.subgroup ? proto.subgroup : ""},
		message_{proto.message} {
	}

}

void badhron_print_report(badhron::CheckReport::Prototype *report) {
	std::cout << "Report incoming!\n";
	std::cout << "Function:\t" << report->function << '\n';
	std::cout << "Subgroup:\t" << (report->subgroup ? report->subgroup : "") << '\n';
	std::cout << "Message:\t" << report->message << '\n';
	std::cout << "Check type:\t" << int(report->ctype) << '\n';
}
