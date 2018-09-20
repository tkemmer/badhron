#ifndef BADHRON_REPORTS_H
#define BADHRON_REPORTS_H

#include <cstdint>
#include <string>

namespace badhron {

	enum class CheckType {
		Bool,
		Int64, Int32, Int16, Int8,
		UInt64, UInt32, UInt16, UInt8,
		Float64, Float32, Float16
	};

	class CheckReport {
	public:
		struct Prototype {
			const char* function;
			const char* subgroup;
			const char* message;
			CheckType   ctype;
			int8_t*     expected;
			int8_t*     observed;
		};

		explicit CheckReport(const Prototype& proto);

	private:
		std::string function_;
		std::string subgroup_;
		std::string message_;
	};
}

extern "C" {
	void badhron_print_report(badhron::CheckReport::Prototype *report);
}

#endif // BADHRON_REPORTS_H
