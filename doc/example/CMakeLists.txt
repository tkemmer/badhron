cmake_minimum_required(VERSION 3.12...3.22)
project(BadhronExample CXX)

find_package(AnyDSL_runtime REQUIRED)
find_package(Badhron REQUIRED)

anydsl_runtime_wrap(BadhronExample_PROGRAM FILES
	${Badhron_IMPALA_FILES}
	main.impala
)

add_executable(badhron_example
	${BadhronExample_PROGRAM}
	main.cpp
)

target_link_libraries(badhron_example ${AnyDSL_runtime_LIBRARIES} Badhron::badhron)
