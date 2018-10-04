cmake_minimum_required(VERSION 3.7 FATAL_ERROR)
project(Badhron CXX)

find_package(AnyDSL_runtime REQUIRED)

set(Badhron_IMPALA_FLAGS "")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_CXX_FLAGS "-Wall -pedantic -fsanitize=address")
	list(APPEND Badhron_IMPALA_FLAGS "-emit-annotated" "-log-level" "debug")
endif()

set(Badhron_IMPALA_FILES
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
	src/cpp/results.cpp
)

target_link_libraries(badhron ${AnyDSL_runtime_LIBRARIES})
set_target_properties(badhron PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

export(TARGETS badhron FILE ${CMAKE_BINARY_DIR}/share/badhron/cmake/badhron-exports.cmake)


#######################################################################################################################
# Tests
anydsl_runtime_wrap(Badhron_TEST_PROGRAM IMPALA_FLAGS ${Badhron_IMPALA_FLAGS} FILES
	${Badhron_IMPALA_FILES}
	test/main.impala
)

add_executable(badhron_test
	${Badhron_TEST_PROGRAM}
	test/main.cpp
)

target_link_libraries(badhron_test badhron ${AnyDSL_runtime_LIBRARIES})
set_target_properties(badhron_test PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
