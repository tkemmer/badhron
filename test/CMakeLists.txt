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
		utils.impala
		${badhron_test}.impala
	)

	add_executable(${badhron_test}
		${${badhron_test}_PROGRAM}
		main.cpp
	)

	target_link_libraries(${badhron_test} badhron)

	add_test(${badhron_test} ${badhron_test})
endforeach ()
