set(Badhron_IMPALA_FILES
	"${PROJECT_SOURCE_DIR}/src/impala/utils.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/reports.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/results.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/checks.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/groups.impala"
	"${PROJECT_SOURCE_DIR}/src/impala/badhron.impala"
)
set(Badhron_IMPALA_FILES ${Badhron_IMPALA_FILES} PARENT_SCOPE)

anydsl_runtime_wrap(Badhron_PROGRAM IMPALA_FLAGS ${Badhron_IMPALA_FLAGS} FILES
	${Badhron_IMPALA_FILES}
)

set(Badhron_HEADER_FILES
	cpp/groups.h
	cpp/reports.h
	cpp/results.h
	cpp/suite.h
)

add_library(badhron SHARED
	${Badhron_PROGRAM}
	cpp/groups.cpp
	cpp/reports.cpp
	cpp/suite.cpp
)
set_target_properties(badhron PROPERTIES BUILD_WITH_INSTALL_RPATH true)
set_target_properties(badhron PROPERTIES PUBLIC_HEADER "${Badhron_HEADER_FILES}")

target_link_libraries(badhron PUBLIC ${AnyDSL_runtime_LIBRARIES})

include(GNUInstallDirs)
install(TARGETS badhron
	EXPORT                    BadhronTargets
	LIBRARY DESTINATION       ${CMAKE_INSTALL_LIBDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/badhron
)

install(EXPORT BadhronTargets
	FILE        BadhronTargets.cmake
	NAMESPACE   Badhron::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/badhron
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("BadhronConfigVersion.cmake"
	VERSION       ${Badhron_VERSION}
	COMPATIBILITY SameMajorVersion
)

install(FILES "../cmake/BadhronConfig.cmake" "${CMAKE_BINARY_DIR}/src/BadhronConfigVersion.cmake"
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/badhron
)

install(FILES ${Badhron_IMPALA_FILES} DESTINATION ${CMAKE_INSTALL_DATADIR}/badhron)
