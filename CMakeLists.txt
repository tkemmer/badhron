cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(Badhron)

find_package(AnyDSL_runtime REQUIRED)

set(badhron_IMPALA_FLAGS "")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	list(APPEND badhron_IMPALA_FLAGS "-emit-annotated" "-log-level" "debug")
endif()

anydsl_runtime_wrap(badhron_PROGRAM IMPALA_FLAGS ${badhron_IMPALA_FLAGS} FILES
	src/facts.impala
	src/results.impala
)
add_library(badhron SHARED ${badhron_PROGRAM})
target_link_libraries(badhron ${AnyDSL_runtime_LIBRARIES})
