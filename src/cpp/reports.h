#ifndef BADHRON_REPORTS_H
#define BADHRON_REPORTS_H

#include <cstdint>
#include <iostream>
#include <memory>
#include <variant>

namespace badhron {

	class report {
	public:
		using data_t = std::variant<bool, int64_t, uint64_t, double>;

		explicit report(
			std::string function,
			std::string subgroup,
			std::string message,
			data_t      expected,
			data_t      observed
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
