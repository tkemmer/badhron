#ifndef BADHRON_RESULTS_H
#define BADHRON_RESULTS_H

#include <cstdint>
#include <iosfwd>
#include <vector>

namespace badhron {

	class report;

	class result_handler {
	public:
		void add_report(report report);
		void print_reports(std::ostream& os) const;

	private:
		std::vector<report> reports_;
	};

}

extern "C" {
	uint64_t badhron_create_result_handler();
	void badhron_delete_result_handler(uint64_t which);

	void badhron_print_reports(uint64_t handler);
	
	void badhron_add_bool_report( uint64_t handler, char* fn, char* subgrp, char* msg, bool     exp, bool     obs);
	void badhron_add_int_report(  uint64_t handler, char* fn, char* subgrp, char* msg, int64_t  exp, int64_t  obs);
	void badhron_add_uint_report( uint64_t handler, char* fn, char* subgrp, char* msg, uint64_t exp, uint64_t obs);
	void badhron_add_float_report(uint64_t handler, char* fn, char* subgrp, char* msg, double   exp, double   obs);
}

#endif
