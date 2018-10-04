#ifndef BADHRON_REPORTS_H
#define BADHRON_REPORTS_H

#include <cstdint>
#include <iostream>
#include <memory>
#include <variant>

namespace badhron {

	using CheckReportData = std::variant<bool, int64_t, uint64_t, double>;

	class CheckReport {
	public:
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

#endif // BADHRON_REPORTS_H
