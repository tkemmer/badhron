#include "reports.h"
#include <iostream>
#include <iomanip>

using namespace std::string_literals;

namespace badhron {

	CheckReport::CheckReport(const Prototype& proto) :
		function_{proto.function},
		subgroup_{proto.subgroup ? proto.subgroup : ""},
		message_{proto.message} {
	}

}

void badhron_print_report(badhron::CheckReport::Prototype* report) {
	std::cout << " # "s << report->function;
	if(report->subgroup)
		std::cout << " (in subgroup "s << report->subgroup << ")"s;
	std::cout << '\n'
	          << "   \e[1m"s << report->message << "\e[0m\n"s;
	switch(report->ctype) {
		case badhron::CheckType::Bool:
			std::cout << std::boolalpha;
			std::cout << "   Expected: "s << *reinterpret_cast<bool*>(report->expected) << '\n';
			std::cout << "   Observed: "s << *reinterpret_cast<bool*>(report->observed) << '\n';
			break;
		case badhron::CheckType::Int64:
			std::cout << "   Expected: "s << *reinterpret_cast<int64_t*>(report->expected) << '\n';
			std::cout << "   Observed: "s << *reinterpret_cast<int64_t*>(report->observed) << '\n';
			break;
		case badhron::CheckType::Int32:
			std::cout << "   Expected: "s << *reinterpret_cast<int32_t*>(report->expected) << '\n';
			std::cout << "   Observed: "s << *reinterpret_cast<int32_t*>(report->observed) << '\n';
			break;
		case badhron::CheckType::Int16:
			std::cout << "   Expected: "s << *reinterpret_cast<int16_t*>(report->expected) << '\n';
			std::cout << "   Observed: "s << *reinterpret_cast<int16_t*>(report->observed) << '\n';
			break;
		case badhron::CheckType::Int8:
			std::cout << "   Expected: "s << int(*report->expected) << '\n';
			std::cout << "   Observed: "s << int(*report->observed) << '\n';
			break;
		case badhron::CheckType::UInt64:
			std::cout << "   Expected: "s << *reinterpret_cast<uint64_t*>(report->expected) << '\n';
			std::cout << "   Observed: "s << *reinterpret_cast<uint64_t*>(report->observed) << '\n';
			break;
		case badhron::CheckType::UInt32:
			std::cout << "   Expected: "s << *reinterpret_cast<uint32_t*>(report->expected) << '\n';
			std::cout << "   Observed: "s << *reinterpret_cast<uint32_t*>(report->observed) << '\n';
			break;
		case badhron::CheckType::UInt16:
			std::cout << "   Expected: "s << *reinterpret_cast<uint16_t*>(report->expected) << '\n';
			std::cout << "   Observed: "s << *reinterpret_cast<uint16_t*>(report->observed) << '\n';
			break;
		case badhron::CheckType::UInt8:
			std::cout << "   Expected: "s << int(*reinterpret_cast<uint8_t*>(report->expected)) << '\n';
			std::cout << "   Observed: "s << int(*reinterpret_cast<uint8_t*>(report->observed)) << '\n';
			break;
		case badhron::CheckType::Float64:
			std::cout << "   Expected: "s << *reinterpret_cast<double*>(report->expected) << '\n';
			std::cout << "   Observed: "s << *reinterpret_cast<double*>(report->observed) << '\n';
			break;
		case badhron::CheckType::Float32:
			std::cout << "   Expected: "s << *reinterpret_cast<float*>(report->expected) << '\n';
			std::cout << "   Observed: "s << *reinterpret_cast<float*>(report->observed) << '\n';
			break;
		default:
			break;
	}
}
