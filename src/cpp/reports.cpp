#include "reports.h"

#include <iomanip>
#include <string>

using namespace std;
using namespace std::string_literals;

namespace badhron {

	// ================================================================================================================
	// check_report::impl
	class check_report::impl {
	public:
		explicit impl(
			std::string function,
			std::string subgroup,
			std::string message,
			check_report_data expected,
			check_report_data observed
		) :
			function_{move(function)},
			subgroup_{move(subgroup)},
			message_ {move(message)},
			expected_{expected},
			observed_{observed} {
		}

		friend ostream& operator<<(ostream& os, const impl& report) {
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
		string            function_;
		string            subgroup_;
		string            message_;
		check_report_data expected_;
		check_report_data observed_;
	};


	// ================================================================================================================
	// check_report
	check_report::check_report(
		std::string function,
		std::string subgroup,
		std::string message,
		check_report_data expected,
		check_report_data observed
	) :
		impl_{make_unique<check_report::impl>(move(function), move(subgroup), move(message), expected, observed)} {
	}

	check_report::check_report(check_report&&) noexcept = default;

	check_report::~check_report() = default;

	check_report& check_report::operator=(badhron::check_report&&) noexcept = default;

	ostream& operator<<(ostream& os, const check_report& report) {
		if(report.impl_)
			os << *report.impl_;
		return os;
	}
}
