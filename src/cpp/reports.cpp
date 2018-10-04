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
			if(holds_alternative<bool>(report.expected_))
				os << boolalpha;
			os << " # "s << report.function_;
			if(report.subgroup_ != ""s)
				os << " (in subgroup "s << report.subgroup_ << ")"s;
			os << '\n'
			   << "   \033[1m"s << report.message_ << "\033[0m\n"s
			   << "   Expected: "s;
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
