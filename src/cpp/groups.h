#ifndef BADHRON_GROUPS_H
#define BADHRON_GROUPS_H

#include "results.h"

#include <iosfwd>
#include <string>
#include <vector>

namespace badhron {
	class report;

	class subgroup {
	public:
		explicit subgroup(std::string name) : name_{move(name)} {}

		result subgroup_result() const noexcept { return result_; }

		void subgroup_result(result result) noexcept { result_ = result; }

		friend std::ostream& operator<<(std::ostream& os, const subgroup& sub);

	private:
		std::string name_;
		result      result_;
	};

	class group {
	public:
		explicit group(std::string name) : name_{move(name)} {}

		void add_subgroup(std::string name);
		void add_report(report);

		result total_result() const noexcept;

		void group_result(result result) noexcept { result_ = result; }
		void subgroup_result(result) noexcept;

		friend std::ostream& operator<<(std::ostream& os, const group& group);

	private:
		std::string           name_;
		result                result_;
		std::vector<subgroup> subgroups_;
		std::vector<report>   reports_;
	};

}

#endif // BADHRON_GROUPS_H
