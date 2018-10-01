#ifndef BADHRON_REPORTS_H
#define BADHRON_REPORTS_H

#include <cstdint>
#include <iostream>
#include <string>

namespace badhron {

	enum class CheckType {
		Bool,
		Int64, Int32, Int16, Int8,
		UInt64, UInt32, UInt16, UInt8,
		Float64, Float32, Float16
	};

	struct CheckReportPrototype {
		const char* function;
		const char* subgroup;
		const char* message;
		CheckType   ctype;
		int8_t*     expected;
		int8_t*     observed;
	};

	template<class T>
	class CheckReport {
	public:
		explicit CheckReport(const CheckReportPrototype& proto) :
			function_{proto.function},
			subgroup_{proto.subgroup ? proto.subgroup : ""},
			message_{proto.message},
			expected_{*reinterpret_cast<T*>(proto.expected)},
			observed_{*reinterpret_cast<T*>(proto.observed)} {
		}

		friend std::ostream& operator<<(std::ostream& os, const CheckReport<T>& report) {
			using namespace std::string_literals;
			os << " # "s << report.function_;
			if(report.subgroup_ != ""s)
				os << " (in subgroup "s << report.subgroup_ << ")"s;
			os << '\n'
			   << "   \e[1m"s << report.message_ << "\e[0m\n"s
			   << "   Expected: "s << report.expected_ << '\n'
			   << "   Observed: "s << report.observed_ << '\n';
			return os;
		}

	private:
		std::string function_;
		std::string subgroup_;
		std::string message_;
		T expected_;
		T observed_;
	};
}

extern "C" {
	void badhron_print_report(badhron::CheckReportPrototype *report);
}

#endif // BADHRON_REPORTS_H
