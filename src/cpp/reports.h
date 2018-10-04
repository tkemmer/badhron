#ifndef BADHRON_REPORTS_H
#define BADHRON_REPORTS_H

#include <cstdint>
#include <iostream>
#include <memory>
#include <variant>

namespace badhron {

	using check_report_data = std::variant<bool, int64_t, uint64_t, double>;

	class check_report {
	public:
		explicit check_report(
			std::string function,
			std::string subgroup,
			std::string message,
			check_report_data expected,
			check_report_data observed
		);

		check_report(const check_report&) = delete;
		check_report(check_report&&) noexcept;

		~check_report();

		check_report& operator=(const check_report&) = delete;
		check_report& operator=(check_report&&) noexcept;

		friend std::ostream &operator<<(std::ostream &os, const check_report &report);

	private:
		class impl;
		std::unique_ptr<impl> impl_;
	};
}

#endif // BADHRON_REPORTS_H
