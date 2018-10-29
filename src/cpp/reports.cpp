#include "reports.h"

#include <iomanip>
#include <string>

namespace badhron {
	using std::ostream;
	using std::string;

	// ================================================================================================================
	// report::impl
	class report::impl {
	public:
		explicit impl(
			string      function,
			string      subgroup,
			string      message,
			report_data expected,
			report_data observed
		) :
			function_{move(function)},
			subgroup_{move(subgroup)},
			message_ {move(message)},
			expected_{expected},
			observed_{observed} {
		}

		friend ostream& operator<<(ostream& os, const impl& report) {
			using namespace std::string_literals;
			if(std::holds_alternative<bool>(report.expected_))
				os << std::boolalpha;
			os << " # "s << report.function_;
			if(report.subgroup_ != ""s)
				os << " (in subgroup "s << report.subgroup_ << ")"s;
			os << '\n'
			   << "   \033[1mAssertion failed: "s << report.message_ << "\033[0m\n"s
			   << "   Expected: "s;
			visit([&os](auto&& arg){ os << arg; }, report.expected_);
			os << '\n'
			   << "   Observed: "s;
			visit([&os](auto&& arg){ os << arg; }, report.observed_);
			os << '\n';
			return os;
		}

	private:
		string      function_;
		string      subgroup_;
		string      message_;
		report_data expected_;
		report_data observed_;
	};


	// ================================================================================================================
	// report
	report::report(
		string      function,
		string      subgroup,
		string      message,
		report_data expected,
		report_data observed
	) :
		impl_{std::make_unique<report::impl>(move(function), move(subgroup), move(message), expected, observed)} {
	}

	report::report(report&&) noexcept = default;

	report::~report() noexcept = default;

	report& report::operator=(badhron::report&&) noexcept = default;

	ostream& operator<<(ostream& os, const report& report) {
		if(report.impl_)
			os << *report.impl_;
		return os;
	}
}
