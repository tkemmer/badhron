#include "reports.h"
#include <iomanip>

void badhron_print_report(badhron::CheckReportPrototype* proto) {
	using badhron::CheckReport;
	std::cout << std::boolalpha;
	switch(proto->ctype) {
		case badhron::CheckType::Bool:
			std::cout << CheckReport<bool>(*proto);
			break;
		case badhron::CheckType::Int64:
			std::cout << CheckReport<int64_t>(*proto);
			break;
		case badhron::CheckType::Int32:
			std::cout << CheckReport<int32_t>(*proto);
			break;
		case badhron::CheckType::Int16:
			std::cout << CheckReport<int16_t>(*proto);
			break;
		case badhron::CheckType::Int8:
			std::cout << CheckReport<int8_t>(*proto);
			break;
		case badhron::CheckType::UInt64:
			std::cout << CheckReport<uint64_t>(*proto);
			break;
		case badhron::CheckType::UInt32:
			std::cout << CheckReport<uint32_t>(*proto);
			break;
		case badhron::CheckType::UInt16:
			std::cout << CheckReport<uint16_t>(*proto);
			break;
		case badhron::CheckType::UInt8:
			std::cout << CheckReport<uint8_t>(*proto);
			break;
		case badhron::CheckType::Float64:
			std::cout << CheckReport<double>(*proto);
			break;
		case badhron::CheckType::Float32:
			std::cout << CheckReport<float>(*proto);
			break;
		default:
			break;
	}
}
