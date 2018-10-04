#include "reports.h"

#include <iomanip>
#include <string>

using namespace std;
using namespace std::string_literals;

namespace badhron {

	// ================================================================================================================
	// CheckReport::Impl
	class CheckReport::Impl {
	public:
		explicit Impl(const CheckReportPrototype& proto) :
			function_{proto.function},
			subgroup_{proto.subgroup},
			message_ {proto.message},
			expected_{},
			observed_{} {

			switch(proto.ctype) {
				case badhron::CheckType::Bool:
					expected_ = *reinterpret_cast<bool*>(proto.expected);
					observed_ = *reinterpret_cast<bool*>(proto.observed);
					break;
				case badhron::CheckType::Int64:
					expected_ = *reinterpret_cast<int64_t*>(proto.expected);
					observed_ = *reinterpret_cast<int64_t*>(proto.observed);
					break;
				case badhron::CheckType::Int32:
					expected_ = *reinterpret_cast<int32_t*>(proto.expected);
					observed_ = *reinterpret_cast<int32_t*>(proto.observed);
					break;
				case badhron::CheckType::Int16:
					expected_ = *reinterpret_cast<int16_t*>(proto.expected);
					observed_ = *reinterpret_cast<int16_t*>(proto.observed);
					break;
				case badhron::CheckType::Int8:
					expected_ = *proto.expected;
					observed_ = *proto.observed;
					break;
				case badhron::CheckType::UInt64:
					expected_ = *reinterpret_cast<uint64_t*>(proto.expected);
					observed_ = *reinterpret_cast<uint64_t*>(proto.observed);
					break;
				case badhron::CheckType::UInt32:
					expected_ = *reinterpret_cast<uint32_t*>(proto.expected);
					observed_ = *reinterpret_cast<uint32_t*>(proto.observed);
					break;
				case badhron::CheckType::UInt16:
					expected_ = *reinterpret_cast<uint16_t*>(proto.expected);
					observed_ = *reinterpret_cast<uint16_t*>(proto.observed);
					break;
				case badhron::CheckType::UInt8:
					expected_ = *reinterpret_cast<uint8_t*>(proto.expected);
					observed_ = *reinterpret_cast<uint8_t*>(proto.observed);
					break;
				case badhron::CheckType::Float64:
					expected_ = *reinterpret_cast<double*>(proto.expected);
					observed_ = *reinterpret_cast<double*>(proto.observed);
					break;
				case badhron::CheckType::Float32:
					expected_ = *reinterpret_cast<float*>(proto.expected);
					observed_ = *reinterpret_cast<float*>(proto.observed);
					break;
				default:
					break; // TODO throw
			}
		}

		explicit Impl(
			std::string function,
			std::string subgroup,
			std::string message,
			CheckReportData expected,
			CheckReportData observed
		) :
			function_{move(function)},
			subgroup_{move(subgroup)},
			message_ {move(message)},
			expected_{expected},
			observed_{observed} {
		}

		friend ostream& operator<<(ostream& os, const Impl& report) {
			os << " # "s << report.function_;
			if(report.subgroup_ != ""s)
				os << " (in subgroup "s << report.subgroup_ << ")"s;
			os << '\n'
			   << "   \033[1m"s << report.message_ << "\033[0m\n"s;
			visit([&os](auto&& arg){ os << arg; }, report.expected_);
			os << '\n'
			   << "   Observed: "s;
			visit([&os](auto&& arg){ os << arg; }, report.observed_);
			os << '\n';
			return os;
		}

	private:
		string          function_;
		string          subgroup_;
		string          message_;
		CheckReportData expected_;
		CheckReportData observed_;
	};

	// ================================================================================================================
	// CheckReport
	CheckReport::CheckReport(const CheckReportPrototype& proto) :
		impl_{make_unique<CheckReport::Impl>(proto)} {
	}

	CheckReport::CheckReport(
		std::string function,
		std::string subgroup,
		std::string message,
		CheckReportData expected,
		CheckReportData observed
	) :
		impl_{make_unique<CheckReport::Impl>(move(function), move(subgroup), move(message), expected, observed)} {
	}

	CheckReport::CheckReport(CheckReport&&) noexcept = default;

	CheckReport::~CheckReport() = default;

	CheckReport& CheckReport::operator=(badhron::CheckReport&&) noexcept = default;

	ostream& operator<<(ostream& os, const CheckReport& report) {
		if(report.impl_)
			os << *report.impl_;
		return os;
	}
}

// ====================================================================================================================
// Impala interface
void badhron_print_report(badhron::CheckReportPrototype* proto) {
	using badhron::CheckReport;
	std::cout << std::boolalpha
	          << CheckReport{*proto};
}
