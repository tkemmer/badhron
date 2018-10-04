#ifndef BADHRON_RESULTS_H
#define BADHRON_RESULTS_H

#include <cstdint>
#include <iosfwd>
#include <vector>

namespace badhron {

	class group;
	class report;

	struct result {
		enum class verdict {passed, failed, pending, none};

		inline constexpr verdict verdict() const noexcept {
			if(failed != 0)
				return verdict::failed;
			if(passed != 0)
				return verdict::passed;
			if(pending != 0)
				return verdict::pending;
			return verdict::none;
		}

		inline constexpr bool empty() const noexcept {
			return passed + failed + pending == 0;
		}

		inline constexpr result& operator+=(const result& other) noexcept {
			passed  += other.passed;
			failed  += other.failed;
			pending += other.pending;
			return *this;
		}

		int32_t passed  {0};
		int32_t failed  {0};
		int32_t pending {0};
	};

	inline result& operator+(result first, const result& second) noexcept {
		return first += second;
	}


	// TODO rename and move (suite)
	class result_handler {
	public:
		void add_group(std::string name);
		void add_subgroup(std::string name);
		void add_report(report);

		void group_result(result);
		void subgroup_result(result);

		friend std::ostream& operator<<(std::ostream& os, const result_handler& handler);

	private:
		std::vector<group>  groups_;
	};

}

extern "C" {
	uint64_t badhron_create_result_handler();
	void badhron_delete_result_handler(uint64_t which);

	void badhron_add_group(uint64_t handler, char* name);
	void badhron_add_subgroup(uint64_t handler, char* name);

	void badhron_set_group_result(uint64_t handler, int32_t passed, int32_t failed, int32_t pending);
	void badhron_set_subgroup_result(uint64_t handler, int32_t passed, int32_t failed, int32_t pending);

	void badhron_print_suite(uint64_t handler);

	void badhron_add_bool_report( uint64_t handler, char* fn, char* subgrp, char* msg, bool     exp, bool     obs);
	void badhron_add_int_report(  uint64_t handler, char* fn, char* subgrp, char* msg, int64_t  exp, int64_t  obs);
	void badhron_add_uint_report( uint64_t handler, char* fn, char* subgrp, char* msg, uint64_t exp, uint64_t obs);
	void badhron_add_float_report(uint64_t handler, char* fn, char* subgrp, char* msg, double   exp, double   obs);
}

#endif
