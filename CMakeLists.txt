cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(Badhron)

find_package(AnyDSL_runtime REQUIRED)

set(badhron_IMPALA_FLAGS "")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	list(APPEND badhron_IMPALA_FLAGS "-emit-annotated" "-log-level" "debug")
endif()

anydsl_runtime_wrap(badhron_PROGRAM IMPALA_FLAGS ${badhron_IMPALA_FLAGS} FILES
	src/results.impala
	src/checks.impala
	src/groups.impala
	src/badhron.impala
	test/main.impala
)

add_executable(badhron_test ${badhron_PROGRAM} test/main.cpp)
target_link_libraries(badhron_test ${AnyDSL_runtime_LIBRARIES})

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/share/badhron/cmake)
configure_file(cmake/badhron-config.cmake.in ${CMAKE_BINARY_DIR}/share/badhron/cmake/badhron-config.cmake @ONLY)
