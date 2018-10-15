#ifndef BADHRON_REPORTS_H
#define BADHRON_REPORTS_H

#include <cstdint>
#include <iostream>
#include <memory>
#include <variant>

namespace badhron {

	using report_data = std::variant<bool, int64_t, uint64_t, double>;

	class report {
	public:
		explicit report(
			std::string function,
			std::string subgroup,
			std::string message,
			report_data expected,
			report_data observed
		);

		report(const report&) = delete;
		report(report&&) noexcept;

		~report() noexcept;

		report& operator=(const report&) = delete;
		report& operator=(report&&) noexcept;

		friend std::ostream &operator<<(std::ostream &os, const report &report);

	private:
		class impl;
		std::unique_ptr<impl> impl_;
	};
}

#endif // BADHRON_REPORTS_H
