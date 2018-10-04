#ifndef BADHRON_RESULTS_H
#define BADHRON_RESULTS_H

#include <cstdint>
#include <iosfwd>
#include <vector>

namespace badhron {

	class CheckReport;

	class ResultHandler {
	public:
		void add_report(CheckReport report);
		void print_reports(std::ostream& os);

	private:
		std::vector<CheckReport> reports_;
	};

}

extern "C" {
	uint64_t badhron_create_result_handler();
	void badhron_delete_result_handler(uint64_t which);

	void badhron_print_reports(uint64_t handler);
	
	void badhron_add_bool_report(uint64_t handler, char* fn, char* subgrp, char* msg, bool     exp, bool     obs);
	void badhron_add_i64_report( uint64_t handler, char* fn, char* subgrp, char* msg, int64_t  exp, int64_t  obs);
	void badhron_add_i32_report( uint64_t handler, char* fn, char* subgrp, char* msg, int32_t  exp, int32_t  obs);
	void badhron_add_i16_report( uint64_t handler, char* fn, char* subgrp, char* msg, int16_t  exp, int16_t  obs);
	void badhron_add_i8_report(  uint64_t handler, char* fn, char* subgrp, char* msg, int8_t   exp, int8_t   obs);
	void badhron_add_u64_report( uint64_t handler, char* fn, char* subgrp, char* msg, uint64_t exp, uint64_t obs);
	void badhron_add_u32_report( uint64_t handler, char* fn, char* subgrp, char* msg, uint32_t exp, uint32_t obs);
	void badhron_add_u16_report( uint64_t handler, char* fn, char* subgrp, char* msg, uint16_t exp, uint16_t obs);
	void badhron_add_u8_report(  uint64_t handler, char* fn, char* subgrp, char* msg, uint8_t  exp, uint8_t  obs);
	void badhron_add_f64_report( uint64_t handler, char* fn, char* subgrp, char* msg, double   exp, double   obs);
	void badhron_add_f32_report( uint64_t handler, char* fn, char* subgrp, char* msg, float    exp, float    obs);
}

#endif
