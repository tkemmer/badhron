#include "results.h"
#include "reports.h"

#include <map>
#include <iostream>

namespace badhron {
	static uint64_t last_handler_id = 0;
	static std::map<uint64_t, ResultHandler> handlers;

	void ResultHandler::add_report(CheckReport report) {
		reports_.push_back(std::move(report));
	}

	void ResultHandler::print_reports(std::ostream& os) {
		if(reports_.empty())
			return;
		for(auto& report: reports_)
			os << report;
		os << "================================================================================\n";
	}
}

uint64_t badhron_create_result_handler() {
	badhron::handlers[badhron::last_handler_id];
	return badhron::last_handler_id++;
}

void badhron_delete_result_handler(uint64_t which) {
	badhron::handlers.erase(which);
}

void badhron_print_reports(uint64_t handler) {
	badhron::handlers[handler].print_reports(std::cout);
}

void badhron_add_bool_report(uint64_t handler, char* fn, char* subgrp, char* msg, bool exp, bool obs) {
	badhron::handlers[handler].add_report(badhron::CheckReport{fn, subgrp, msg, exp, obs});
}

void badhron_add_i64_report(uint64_t handler, char* fn, char* subgrp, char* msg, int64_t exp, int64_t obs) {
	badhron::handlers[handler].add_report(badhron::CheckReport{fn, subgrp, msg, exp, obs});
}

void badhron_add_i32_report(uint64_t handler, char* fn, char* subgrp, char* msg, int32_t exp, int32_t obs) {
	badhron::handlers[handler].add_report(badhron::CheckReport{fn, subgrp, msg, exp, obs});
}

void badhron_add_i16_report(uint64_t handler, char* fn, char* subgrp, char* msg, int16_t exp, int16_t obs) {
	badhron::handlers[handler].add_report(badhron::CheckReport{fn, subgrp, msg, exp, obs});
}

void badhron_add_i8_report(uint64_t handler, char* fn, char* subgrp, char* msg, int8_t exp, int8_t obs) {
	badhron::handlers[handler].add_report(badhron::CheckReport{fn, subgrp, msg, exp, obs});
}

void badhron_add_u64_report(uint64_t handler, char* fn, char* subgrp, char* msg, uint64_t exp, uint64_t obs) {
	badhron::handlers[handler].add_report(badhron::CheckReport{fn, subgrp, msg, exp, obs});
}

void badhron_add_u32_report(uint64_t handler, char* fn, char* subgrp, char* msg, uint32_t exp, uint32_t obs) {
	badhron::handlers[handler].add_report(badhron::CheckReport{fn, subgrp, msg, exp, obs});
}

void badhron_add_u16_report(uint64_t handler, char* fn, char* subgrp, char* msg, uint16_t exp, uint16_t obs) {
	badhron::handlers[handler].add_report(badhron::CheckReport{fn, subgrp, msg, exp, obs});
}

void badhron_add_u8_report(uint64_t handler, char* fn, char* subgrp, char* msg, uint8_t exp, uint8_t obs) {
	badhron::handlers[handler].add_report(badhron::CheckReport{fn, subgrp, msg, exp, obs});
}

void badhron_add_f64_report(uint64_t handler, char* fn, char* subgrp, char* msg, double exp, double obs) {
	badhron::handlers[handler].add_report(badhron::CheckReport{fn, subgrp, msg, exp, obs});
}

void badhron_add_f32_report(uint64_t handler, char* fn, char* subgrp, char* msg, float exp, float obs) {
	badhron::handlers[handler].add_report(badhron::CheckReport{fn, subgrp, msg, exp, obs});
}
