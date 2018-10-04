#ifndef BADHRON_RESULTS_H
#define BADHRON_RESULTS_H

#include <cstdint>

namespace badhron {

	class ResultHandler {

	};

}

extern "C" {
	uint64_t badhron_create_result_handler();
	void badhron_delete_result_handler(uint64_t which);
}

#endif
