#include "groups.h"

#include "reports.h"

#include <memory>
#include <numeric>
#include <ostream>

namespace badhron {
	using std::move;
	using std::ostream;
	using std::string;

	// ================================================================================================================
	// helper functions
	void print_short_summary(ostream& os, const result& result) {
		using namespace std::string_literals;
		if(result.passed + result.failed + result.pending > 0) {
			os << " ("s;
			if(result.failed > 0) {
				os << result.failed << " failed"s;
				if(result.passed + result.pending > 0)
					os << ", "s;
			}
			if(result.passed > 0) {
				os << result.passed << " passed"s;
				if(result.pending > 0)
					os << ", "s;
			}
			if(result.pending > 0)
				os << result.pending << " pending"s;
			os << ")\n"s;
		}
	}


	// ================================================================================================================
	// subgroup
	ostream& operator<<(ostream& os, const subgroup& sub) {
		using namespace std::string_literals;
		os << " > "s << sub.name_;
		print_short_summary(os, sub.result_);
		return os;
	}


	// ================================================================================================================
	// group
	void group::add_subgroup(std::string name) {
		subgroups_.emplace_back(move(name));
	}

	void group::add_report(report report) {
		reports_.emplace_back(move(report));
	}

	result group::total_result() const noexcept {
		return std::accumulate(subgroups_.begin(), subgroups_.end(), result_, [](auto sum, const auto& sub) {
			return sum + sub.subgroup_result();
		});
	}

	void group::subgroup_result(result result) noexcept {
		if(!subgroups_.empty())
			subgroups_.back().subgroup_result(result);
	}

	ostream& operator<<(ostream& os, const group& group) {
		using namespace std::string_literals;
		os << "\033[1mGRP\033[0m "s << group.name_ << '\n'
		   << "================================================================================\n"s;
		if(!group.subgroups_.empty()) {
			for(const auto& sub: group.subgroups_)
				os << sub;
			if(!group.result_.empty()) {
				os << " + group checks"s;
				print_short_summary(os, group.result_);
			}
			os << "================================================================================\n"s;
		}
		if(!group.reports_.empty()) {
			for(const auto& rep: group.reports_)
				os << rep;
			os << "================================================================================\n"s;
		}
		auto total = group.total_result();
		switch(total.verdict()) {
			case result::verdict::passed:
				os << "\033[1m"s << total.passed << " PASSED ✓\033[0m"s;
				print_short_summary(os, {0, total.failed, total.pending});
				break;
			case result::verdict::failed:
				os << "\033[1m"s << total.failed << " FAILED\033[0m"s;
				print_short_summary(os, {total.passed, 0, total.pending});
				break;

			case result::verdict::pending:
				os << "\033[1m"s << total.pending << " PENDING\033[0m"s;
				break;
			default:
				break;
		}
		return os << '\n';
	}
}
