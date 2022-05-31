# Badhron configuration file
#
# This will define the following variables:
# - Badhron_IMPALA_FILES   // source files to be included in your project's anydsl_runtime_wrap call
# - Badhron_INCLUDE_DIRS   // root directory of Badhron's header files
# - Badhron_LIBRARIES      // Badhron libraries to be included in your project's target_link_libraries call

include(GNUInstallDirs)
find_path(Badhron_DATA_DIR NAMES badhron.impala PATH_SUFFIXES "${CMAKE_INSTALL_DATADIR}/badhron")
mark_as_advanced(Badhron_DATA_DIR)

find_path(Badhron_INCLUDE_DIR NAMES badhron/suite.h)
mark_as_advanced(Badhron_INCLUDE_DIR)

find_library(Badhron_LIBRARY NAMES badhron)
mark_as_advanced(Badhron_LIBRARY)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Badhron DEFAULT_MSG
	Badhron_DATA_DIR
	Badhron_INCLUDE_DIR
	Badhron_LIBRARY
)

include(CMakeFindDependencyMacro)
find_dependency(AnyDSL_runtime REQUIRED)

if(Badhron_FOUND)
	set(Badhron_IMPALA_FILES
		"${Badhron_DATA_DIR}/utils.impala"
		"${Badhron_DATA_DIR}/reports.impala"
		"${Badhron_DATA_DIR}/results.impala"
		"${Badhron_DATA_DIR}/checks.impala"
		"${Badhron_DATA_DIR}/groups.impala"
		"${Badhron_DATA_DIR}/badhron.impala"
	)
	set(Badhron_INCLUDE_DIRS ${Badhron_INCLUDE_DIR})
	set(Badhron_LIBRARIES    ${Badhron_LIBRARY})
	if(NOT TARGET Badhron::badhron)
		include("${CMAKE_CURRENT_LIST_DIR}/BadhronTargets.cmake")
	endif()
endif()
