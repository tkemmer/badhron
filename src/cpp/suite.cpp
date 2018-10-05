#include "suite.h"

#include "groups.h"
#include "reports.h"

#include <iostream>
#include <map>
#include <string>

namespace badhron {
	using std::move;
	using std::ostream;
	using std::string;

	static uint64_t last_handler_id = 0;
	static std::map<uint64_t, result_handler> handlers;

	void result_handler::add_group(string name) {
		groups_.emplace_back(move(name));
	}

	void result_handler::add_subgroup(std::string name) {
		if(!groups_.empty()) // TODO else
			groups_.back().add_subgroup(move(name));
	}

	void result_handler::add_report(report report) {
		if(!groups_.empty()) // TODO else
			groups_.back().add_report(move(report));
	}

	void result_handler::group_result(result result) {
		if(!groups_.empty()) // TODO else
			groups_.back().group_result(result);
	}

	void result_handler::subgroup_result(result result) {
		if(!groups_.empty()) // TODO else
			groups_.back().subgroup_result(result);
	}

	ostream& operator<<(ostream& os, const result_handler& handler) {
		for(auto& group: handler.groups_)
			std::cout << group;
		return os;
	}
}

uint64_t badhron_create_result_handler() {
	badhron::handlers[badhron::last_handler_id];
	return badhron::last_handler_id++;
}

void badhron_delete_result_handler(uint64_t which) {
	badhron::handlers.erase(which);
}

void badhron_add_group(uint64_t handler, char* name) {
	badhron::handlers[handler].add_group(name);
}

void badhron_add_subgroup(uint64_t handler, char* name) {
	badhron::handlers[handler].add_subgroup(name);
}

void badhron_set_group_result(uint64_t handler, int32_t passed, int32_t failed, int32_t pending) {
	badhron::handlers[handler].group_result(badhron::result{passed, failed, pending});
}

void badhron_set_subgroup_result(uint64_t handler, int32_t passed, int32_t failed, int32_t pending) {
	badhron::handlers[handler].subgroup_result(badhron::result{passed, failed, pending});
}

void badhron_print_suite(uint64_t handler) {
	std::cout << badhron::handlers[handler];
}

void badhron_add_bool_report(uint64_t handler, char* fn, char* subgrp, char* msg, bool exp, bool obs) {
	badhron::handlers[handler].add_report(badhron::report{fn, subgrp, msg, exp, obs});
}

void badhron_add_int_report(uint64_t handler, char* fn, char* subgrp, char* msg, int64_t exp, int64_t obs) {
	badhron::handlers[handler].add_report(badhron::report{fn, subgrp, msg, exp, obs});
}

void badhron_add_uint_report(uint64_t handler, char* fn, char* subgrp, char* msg, uint64_t exp, uint64_t obs) {
	badhron::handlers[handler].add_report(badhron::report{fn, subgrp, msg, exp, obs});
}

void badhron_add_float_report(uint64_t handler, char* fn, char* subgrp, char* msg, double exp, double obs) {
	badhron::handlers[handler].add_report(badhron::report{fn, subgrp, msg, exp, obs});
}
