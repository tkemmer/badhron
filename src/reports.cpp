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
			std::cout << "Expected:\t" << *reinterpret_cast<bool*>(report->expected) << '\n';
			std::cout << "Observed:\t" << *reinterpret_cast<bool*>(report->observed) << '\n';
			break;
		case badhron::CheckType::Int64:
			std::cout << "Expected:\t" << *reinterpret_cast<int64_t*>(report->expected) << '\n';
			std::cout << "Observed:\t" << *reinterpret_cast<int64_t*>(report->observed) << '\n';
			break;
		case badhron::CheckType::Int32:
			std::cout << "Expected:\t" << *reinterpret_cast<int32_t*>(report->expected) << '\n';
			std::cout << "Observed:\t" << *reinterpret_cast<int32_t*>(report->observed) << '\n';
			break;
		case badhron::CheckType::Int16:
			std::cout << "Expected:\t" << *reinterpret_cast<int16_t*>(report->expected) << '\n';
			std::cout << "Observed:\t" << *reinterpret_cast<int16_t*>(report->observed) << '\n';
			break;
		case badhron::CheckType::Int8:
			std::cout << "Expected:\t" << int(*report->expected) << '\n';
			std::cout << "Observed:\t" << int(*report->observed) << '\n';
			break;
		case badhron::CheckType::UInt64:
			std::cout << "Expected:\t" << *reinterpret_cast<uint64_t*>(report->expected) << '\n';
			std::cout << "Observed:\t" << *reinterpret_cast<uint64_t*>(report->observed) << '\n';
			break;
		case badhron::CheckType::UInt32:
			std::cout << "Expected:\t" << *reinterpret_cast<uint32_t*>(report->expected) << '\n';
			std::cout << "Observed:\t" << *reinterpret_cast<uint32_t*>(report->observed) << '\n';
			break;
		case badhron::CheckType::UInt16:
			std::cout << "Expected:\t" << *reinterpret_cast<uint16_t*>(report->expected) << '\n';
			std::cout << "Observed:\t" << *reinterpret_cast<uint16_t*>(report->observed) << '\n';
			break;
		case badhron::CheckType::UInt8:
			std::cout << "Expected:\t" << int(*reinterpret_cast<uint8_t*>(report->expected)) << '\n';
			std::cout << "Observed:\t" << int(*reinterpret_cast<uint8_t*>(report->observed)) << '\n';
			break;
		case badhron::CheckType::Float64:
			std::cout << "Expected:\t" << *reinterpret_cast<double*>(report->expected) << '\n';
			std::cout << "Observed:\t" << *reinterpret_cast<double*>(report->observed) << '\n';
			break;
		case badhron::CheckType::Float32:
			std::cout << "Expected:\t" << *reinterpret_cast<float*>(report->expected) << '\n';
			std::cout << "Observed:\t" << *reinterpret_cast<float*>(report->observed) << '\n';
			break;
		default:
			break;
	}
}
