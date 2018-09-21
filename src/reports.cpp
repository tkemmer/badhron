#include "reports.h"
#include <iostream>
#include <iomanip>

namespace badhron {

	CheckReport::CheckReport(const Prototype& proto) :
		function_{proto.function},
		subgroup_{proto.subgroup ? proto.subgroup : ""},
		message_{proto.message} {
	}

}

void badhron_print_report(badhron::CheckReport::Prototype* report) {
	std::cout << "Report incoming!\n";
	std::cout << "Function:\t" << report->function << '\n';
	std::cout << "Subgroup:\t" << (report->subgroup ? report->subgroup : "") << '\n';
	std::cout << "Message:\t" << report->message << '\n';
	switch(report->ctype) {
		case badhron::CheckType::Bool:
			std::cout << std::boolalpha;
			std::cout << "Expected:\t" << reinterpret_cast<bool*>(report->expected)[0] << '\n';
			std::cout << "Observed:\t" << reinterpret_cast<bool*>(report->observed)[0] << '\n';
			break;
		default:
			break;
	}
}
