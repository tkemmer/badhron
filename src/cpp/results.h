#ifndef BADHRON_RESULTS_H
#define BADHRON_RESULTS_H

#include <cstdint>

namespace badhron {

	struct result {
		enum class verdict {
			passed, failed, pending, none
		};

		constexpr verdict verdict() const noexcept {
			if (failed != 0)
				return verdict::failed;
			if (passed != 0)
				return verdict::passed;
			if (pending != 0)
				return verdict::pending;
			return verdict::none;
		}

		constexpr bool empty() const noexcept {
			return passed + failed + pending == 0;
		}

		constexpr result &operator+=(const result &other) noexcept {
			passed += other.passed;
			failed += other.failed;
			pending += other.pending;
			return *this;
		}

		int32_t passed{0};
		int32_t failed{0};
		int32_t pending{0};
	};

	constexpr result operator+(result first, const result &second) noexcept {
		return first += second;
	}
}

#endif // BADHRON_RESULTS_H
