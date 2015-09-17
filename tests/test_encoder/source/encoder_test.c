/*
 * File:
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "encoder.h"

/*
 * CUnit Test Suite
 */

int init_suite(){
	return 0;
}

int clean_suite(){
	return 0;
}

void test_func1() {
	CU_ASSERT( 0 == 0);
}

int main() {
	CU_TestInfo test_array[] = {
		{"testname1", test_func1},
		CU_TEST_INFO_NULL};

	CU_SuiteInfo suite_array[] = {
		{"window_manager_test", init_suite, clean_suite, test_array},
		CU_SUITE_INFO_NULL};

	/* Initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* Add a suite to the registry */
	if(CUE_SUCCESS != CU_register_suites(suite_array)){
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
