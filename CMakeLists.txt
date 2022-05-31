cmake_minimum_required(VERSION 3.12...3.22)

project(Badhron
	VERSION      0.1
	DESCRIPTION  "Readable Tests for Impala"
	HOMEPAGE_URL "https://github.com/tkemmer/badhron"
	LANGUAGES    CXX
)

# Dependencies
find_package(AnyDSL_runtime REQUIRED)

# Set default properties for all targets
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS}         -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}   -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

set(Badhron_IMPALA_FLAGS "")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	list(APPEND Badhron_IMPALA_FLAGS "-emit-annotated" "-log-level" "debug")
endif()

# Configuration file
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/share/badhron/cmake")
configure_file(cmake/badhron-config.cmake.in "${CMAKE_BINARY_DIR}/share/badhron/cmake/badhron-config.cmake" @ONLY)

# Library
add_subdirectory(src)

# Tests
include(CTest)
if(BUILD_TESTING)
	add_subdirectory(test)
endif()
