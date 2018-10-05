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

	static uint64_t last_suite_id = 0;
	static std::map<uint64_t, suite> suites;

	void suite::add_group(string name) {
		groups_.emplace_back(move(name));
	}

	void suite::add_subgroup(std::string name) {
		if(!groups_.empty()) // TODO else
			groups_.back().add_subgroup(move(name));
	}

	void suite::add_report(report report) {
		if(!groups_.empty()) // TODO else
			groups_.back().add_report(move(report));
	}

	void suite::group_result(result result) {
		if(!groups_.empty()) // TODO else
			groups_.back().group_result(result);
	}

	void suite::subgroup_result(result result) {
		if(!groups_.empty()) // TODO else
			groups_.back().subgroup_result(result);
	}

	ostream& operator<<(ostream& os, const suite& suite) {
		for(auto& group: suite.groups_)
			std::cout << group << '\n';
		return os;
	}
}

uint64_t badhron_create_suite() {
	badhron::suites[badhron::last_suite_id];
	return badhron::last_suite_id++;
}

void badhron_delete_suite(uint64_t which) {
	badhron::suites.erase(which);
}

void badhron_add_group(uint64_t suite, char* name) {
	badhron::suites[suite].add_group(name);
}

void badhron_add_subgroup(uint64_t suite, char* name) {
	badhron::suites[suite].add_subgroup(name);
}

void badhron_set_group_result(uint64_t suite, int32_t passed, int32_t failed, int32_t pending) {
	badhron::suites[suite].group_result(badhron::result{passed, failed, pending});
}

void badhron_set_subgroup_result(uint64_t suite, int32_t passed, int32_t failed, int32_t pending) {
	badhron::suites[suite].subgroup_result(badhron::result{passed, failed, pending});
}

void badhron_print_suite(uint64_t suite) {
	std::cout << badhron::suites[suite];
}

void badhron_add_bool_report(uint64_t suite, char* fn, char* subgrp, char* msg, bool exp, bool obs) {
	badhron::suites[suite].add_report(badhron::report{fn, subgrp, msg, exp, obs});
}

void badhron_add_int_report(uint64_t suite, char* fn, char* subgrp, char* msg, int64_t exp, int64_t obs) {
	badhron::suites[suite].add_report(badhron::report{fn, subgrp, msg, exp, obs});
}

void badhron_add_uint_report(uint64_t suite, char* fn, char* subgrp, char* msg, uint64_t exp, uint64_t obs) {
	badhron::suites[suite].add_report(badhron::report{fn, subgrp, msg, exp, obs});
}

void badhron_add_float_report(uint64_t suite, char* fn, char* subgrp, char* msg, double exp, double obs) {
	badhron::suites[suite].add_report(badhron::report{fn, subgrp, msg, exp, obs});
}
