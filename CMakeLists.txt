cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(Badhron CXX)

find_package(AnyDSL_runtime REQUIRED)

set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS}         -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}   -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

set(Badhron_IMPALA_FLAGS "")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	list(APPEND Badhron_IMPALA_FLAGS "-emit-annotated" "-log-level" "debug")
endif()

set(Badhron_IMPALA_FILES
	src/impala/utils.impala
	src/impala/reports.impala
	src/impala/results.impala
	src/impala/checks.impala
	src/impala/groups.impala
	src/impala/badhron.impala
)

#######################################################################################################################
# Configuration file
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/share/badhron/cmake)
configure_file(cmake/badhron-config.cmake.in ${CMAKE_BINARY_DIR}/share/badhron/cmake/badhron-config.cmake @ONLY)


#######################################################################################################################
# Library
anydsl_runtime_wrap(Badhron_PROGRAM IMPALA_FLAGS ${badhron_IMPALA_FLAGS} FILES
	${Badhron_IMPALA_FILES}
)

add_library(badhron SHARED
	${Badhron_PROGRAM}
	src/cpp/groups.h
	src/cpp/groups.cpp
	src/cpp/reports.h
	src/cpp/reports.cpp
	src/cpp/results.h
	src/cpp/suite.h
	src/cpp/suite.cpp
)

target_link_libraries(badhron ${AnyDSL_runtime_LIBRARIES})
set_target_properties(badhron PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

export(TARGETS badhron FILE ${CMAKE_BINARY_DIR}/share/badhron/cmake/badhron-exports.cmake)


#######################################################################################################################
# Tests
enable_testing()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test)

set(Badhron_TESTS
	example_builtin
	example_custom
	test_approx_f32
	test_approx_f64
	test_create_suite
	test_delete_suite
	test_pending
	test_assert_bool
	test_assert_int
	test_assert_uint
	test_assert_float
	test_check_result
	test_result_handler
	test_result_handler_init
	test_result_handler_groups
	test_result_handler_subgroups
	test_result_handler_mixed
)

foreach(badhron_test ${Badhron_TESTS})
	anydsl_runtime_wrap(${badhron_test}_PROGRAM IMPALA_FLAGS ${Badhron_IMPALA_FLAGS} FILES
		${Badhron_IMPALA_FILES}
		test/utils.impala
		test/${badhron_test}.impala
	)

	add_executable(${badhron_test}
		${${badhron_test}_PROGRAM}
		test/main.cpp
	)

	target_link_libraries(${badhron_test} badhron ${AnyDSL_runtime_LIBRARIES})
	set_target_properties(${badhron_test} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

	add_test(${badhron_test} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${badhron_test})
endforeach ()
