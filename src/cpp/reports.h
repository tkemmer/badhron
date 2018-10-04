#ifndef BADHRON_REPORTS_H
#define BADHRON_REPORTS_H

#include <cstdint>
#include <iostream>
#include <memory>
#include <variant>

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

	using CheckReportData = std::variant<
		bool,
		int64_t, int32_t, int16_t, int8_t,
		uint64_t, uint32_t, uint16_t, uint8_t,
		double, float
	>;

	class CheckReport {
	public:
		explicit CheckReport(const CheckReportPrototype &proto);

		explicit CheckReport(
			std::string function,
			std::string subgroup,
			std::string message,
			CheckReportData expected,
			CheckReportData observed
		);

		CheckReport(const CheckReport&) = delete;
		CheckReport(CheckReport&&) noexcept;

		~CheckReport();

		CheckReport& operator=(const CheckReport&) = delete;
		CheckReport& operator=(CheckReport&&) noexcept;

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
