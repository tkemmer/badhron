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

add_library(badhron SHARED
	${Badhron_PROGRAM}
	cpp/groups.h
	cpp/groups.cpp
	cpp/reports.h
	cpp/reports.cpp
	cpp/results.h
	cpp/suite.h
	cpp/suite.cpp
)

target_link_libraries(badhron PUBLIC ${AnyDSL_runtime_LIBRARIES})

export(TARGETS badhron FILE "${CMAKE_BINARY_DIR}/share/badhron/cmake/badhron-exports.cmake")
