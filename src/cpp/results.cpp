#include "results.h"

#include <map>

namespace badhron {
	static uint64_t last_handler_id = 0;
	static std::map<uint64_t, ResultHandler> handlers;
}

uint64_t badhron_create_result_handler() {
	badhron::handlers[badhron::last_handler_id];
	return badhron::last_handler_id++;
}

void badhron_delete_result_handler(uint64_t which) {
	badhron::handlers.erase(which);
}
