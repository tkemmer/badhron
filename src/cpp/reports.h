#ifndef BADHRON_REPORTS_H
#define BADHRON_REPORTS_H

#include <cstdint>
#include <iostream>
#include <memory>

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

	class CheckReport {
	public:
		explicit CheckReport(const CheckReportPrototype &proto);
		~CheckReport();

		friend std::ostream &operator<<(std::ostream &os, const CheckReport &report);

	private:
		class Impl;
		std::unique_ptr<Impl> impl_;
	};
}

extern "C" {
	void badhron_print_report(badhron::CheckReportPrototype *report);
}

#endif // BADHRON_REPORTS_H
