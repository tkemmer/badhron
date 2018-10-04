#include "results.h"
#include "reports.h"

#include <map>
#include <iostream>

namespace badhron {
	static uint64_t last_handler_id = 0;
	static std::map<uint64_t, result_handler> handlers;

	void result_handler::add_report(check_report report) {
		reports_.push_back(std::move(report));
	}

	void result_handler::print_reports(std::ostream& os) const {
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
	badhron::handlers[handler].add_report(badhron::check_report{fn, subgrp, msg, exp, obs});
}

void badhron_add_int_report(uint64_t handler, char* fn, char* subgrp, char* msg, int64_t exp, int64_t obs) {
	badhron::handlers[handler].add_report(badhron::check_report{fn, subgrp, msg, exp, obs});
}

void badhron_add_uint_report(uint64_t handler, char* fn, char* subgrp, char* msg, uint64_t exp, uint64_t obs) {
	badhron::handlers[handler].add_report(badhron::check_report{fn, subgrp, msg, exp, obs});
}

void badhron_add_float_report(uint64_t handler, char* fn, char* subgrp, char* msg, double exp, double obs) {
	badhron::handlers[handler].add_report(badhron::check_report{fn, subgrp, msg, exp, obs});
}
