#ifndef BADHRON_RESULTS_H
#define BADHRON_RESULTS_H

#include <cstdint>

namespace badhron {

	struct result {
		enum class verdict {
			passed, failed, pending, none
		};

		constexpr result() noexcept :
			passed{0},
			failed{0},
			pending{0} {
		}

		explicit constexpr result(int32_t passed, int32_t failed, int32_t pending) noexcept :
				passed{passed},
				failed{failed},
				pending{pending} {
		}

		constexpr result(const result& other) noexcept = default;
		constexpr result(result&& other) noexcept = default;

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

		constexpr result& operator=(const result& other) noexcept = default;
		constexpr result& operator=(result&& other) noexcept = default;

		constexpr result& operator+=(const result& other) noexcept {
			passed += other.passed;
			failed += other.failed;
			pending += other.pending;
			return *this;
		}

		int32_t passed;
		int32_t failed;
		int32_t pending;
	};

	constexpr result operator+(result first, const result& second) noexcept {
		return first += second;
	}
}

#endif // BADHRON_RESULTS_H
