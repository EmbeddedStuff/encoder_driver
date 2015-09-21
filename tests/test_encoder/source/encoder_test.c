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
	encoder_handle myEncoder =  encoder_new();
	CU_ASSERT( myEncoder != NULL);
	CU_ASSERT( encoder_getPosition(myEncoder) == 0);
}

void increase_encoder_by_one(encoder_handle myEncoder){
	encoder_postEvent(myEncoder, 1, 1);
	encoder_postEvent(myEncoder, 1, 0);
	encoder_postEvent(myEncoder, 0, 0);
	encoder_postEvent(myEncoder, 0, 1);
	encoder_postEvent(myEncoder, 1, 1);
}

void decrease_encoder_by_one(encoder_handle myEncoder){
	encoder_postEvent(myEncoder, 1, 1);
	encoder_postEvent(myEncoder, 0, 1);
	encoder_postEvent(myEncoder, 0, 0);
	encoder_postEvent(myEncoder, 1, 0);
	encoder_postEvent(myEncoder, 1, 1);
}

void test_func2() {
	encoder_handle myEncoder =  encoder_new();
	increase_encoder_by_one(myEncoder);
	CU_ASSERT( encoder_getPosition(myEncoder) == 1);
}

void test_func3() {
	encoder_handle myEncoder =  encoder_new();
	decrease_encoder_by_one(myEncoder);
	CU_ASSERT( encoder_getPosition(myEncoder) == -1);
}

void test_func4() {
	encoder_handle myEncoder =  encoder_new();
	increase_encoder_by_one(myEncoder);
	increase_encoder_by_one(myEncoder);
	CU_ASSERT( encoder_getPosition(myEncoder) == 2);
}

void test_func5() {
	encoder_handle myEncoder =  encoder_new();
	decrease_encoder_by_one(myEncoder);
	decrease_encoder_by_one(myEncoder);
	CU_ASSERT( encoder_getPosition(myEncoder) == -2);
}

void test_func6() {
	encoder_handle myEncoder =  encoder_new();
	increase_encoder_by_one(myEncoder);
	decrease_encoder_by_one(myEncoder);
	CU_ASSERT( encoder_getPosition(myEncoder) == 0);
}

void test_func7() {
	encoder_handle myEncoder =  encoder_new();
	decrease_encoder_by_one(myEncoder);
	increase_encoder_by_one(myEncoder);
	CU_ASSERT( encoder_getPosition(myEncoder) == 0);
}

void fake_increment(encoder_handle myEncoder){
	encoder_postEvent(myEncoder, 1, 1);
	encoder_postEvent(myEncoder, 1, 0);
	encoder_postEvent(myEncoder, 0, 0);
	encoder_postEvent(myEncoder, 1, 0);
	encoder_postEvent(myEncoder, 1, 1);
}

void test_func8() {
	encoder_handle myEncoder =  encoder_new();
	fake_increment(myEncoder);
	CU_ASSERT( encoder_getPosition(myEncoder) == 0);
}

void fake_decrement(encoder_handle myEncoder){
	encoder_postEvent(myEncoder, 1, 1);
	encoder_postEvent(myEncoder, 0, 1);
	encoder_postEvent(myEncoder, 0, 0);
	encoder_postEvent(myEncoder, 0, 1);
	encoder_postEvent(myEncoder, 1, 1);
}

void test_func9() {
	encoder_handle myEncoder =  encoder_new();
	fake_decrement(myEncoder);
	CU_ASSERT( encoder_getPosition(myEncoder) == 0);
}


void test_func10() {
	encoder_handle myEncoder =  encoder_new();
	fake_increment(myEncoder);
	decrease_encoder_by_one(myEncoder);
	CU_ASSERT( encoder_getPosition(myEncoder) == -1);
}

void test_func11() {
	encoder_handle myEncoder =  encoder_new();
	fake_decrement(myEncoder);
	increase_encoder_by_one(myEncoder);
	CU_ASSERT( encoder_getPosition(myEncoder) == 1);
}

void test_func12() {
	encoder_handle myEncoder =  encoder_new();
	encoder_postEvent(myEncoder, 1, 1);
	encoder_postEvent(myEncoder, 1, 0);
	encoder_postEvent(myEncoder, 1, 1);
	encoder_postEvent(myEncoder, 1, 0);
	encoder_postEvent(myEncoder, 0, 0);
	encoder_postEvent(myEncoder, 1, 0);
	encoder_postEvent(myEncoder, 0, 0);
	encoder_postEvent(myEncoder, 0, 1);
	encoder_postEvent(myEncoder, 0, 0);
	encoder_postEvent(myEncoder, 0, 1);
	encoder_postEvent(myEncoder, 1, 1);
	encoder_postEvent(myEncoder, 0, 1);
	encoder_postEvent(myEncoder, 1, 1);
	CU_ASSERT( encoder_getPosition(myEncoder) == 1);
}

void test_func13() {
	encoder_handle myEncoder =  encoder_new();
	encoder_postEvent(myEncoder, 1, 1);
	encoder_postEvent(myEncoder, 0, 1);
	encoder_postEvent(myEncoder, 1, 1);
	encoder_postEvent(myEncoder, 0, 1);
	encoder_postEvent(myEncoder, 0, 0);
	encoder_postEvent(myEncoder, 0, 1);
	encoder_postEvent(myEncoder, 0, 0);
	encoder_postEvent(myEncoder, 1, 0);
	encoder_postEvent(myEncoder, 0, 0);
	encoder_postEvent(myEncoder, 1, 0);
	encoder_postEvent(myEncoder, 1, 1);
	encoder_postEvent(myEncoder, 1, 0);
	encoder_postEvent(myEncoder, 1, 1);
	CU_ASSERT( encoder_getPosition(myEncoder) == -1);
}


int callbackWasCalled = 0;

void mock_callback(encoder_handle encoder){
	callbackWasCalled = 1;
}

void test_func14() {
	encoder_handle myEncoder =  encoder_new();
	callbackWasCalled = 0;
	encoder_setOnChangeCallback(myEncoder, mock_callback);
	increase_encoder_by_one(myEncoder);
	CU_ASSERT( callbackWasCalled == 1 );
}

void test_func15() {
	encoder_handle myEncoder =  encoder_new();
	callbackWasCalled = 0;
	encoder_setOnChangeCallback(myEncoder, mock_callback);
	decrease_encoder_by_one(myEncoder);
	CU_ASSERT( callbackWasCalled == 1 );
}

int mock_position = 0;
void mock2_callback(encoder_handle encoder){
	mock_position = encoder_getPosition(encoder);
}

void test_func16() {
	encoder_handle myEncoder =  encoder_new();
	mock_position = 0;
	encoder_setOnChangeCallback(myEncoder, mock2_callback);
	increase_encoder_by_one(myEncoder);
	CU_ASSERT( mock_position == 1 );
}

void test_func17() {
	encoder_handle myEncoder =  encoder_new();
	mock_position = 0;
	encoder_setOnChangeCallback(myEncoder, mock2_callback);
	decrease_encoder_by_one(myEncoder);
	CU_ASSERT( mock_position == -1 );
}

int main() {
	CU_TestInfo test_array[] = {
		{"encoder object creation", test_func1},
		{"encoder simple increment", test_func2},
		{"encoder simple decrement", test_func3},
		{"encoder double increment", test_func4},
		{"encoder double decrement", test_func5},
		{"encoder increase-decrease", test_func6},
		{"encoder decrease-increase", test_func7},
		{"encoder false increment ", test_func8},
		{"encoder false decrement", test_func9},
		{"encoder false increment true decrement", test_func10},
		{"encoder false decrement true increment", test_func11},
		{"encoder noisy increment", test_func12},
		{"encoder noisy decrement", test_func13},
		{"that callback is called when increment in generated", test_func14},
		{"that callback is called when decrement in generated", test_func15},
		{"that callback is passed the right position when incrementing ", test_func16},
		{"that callback is passed the right position when decrementing ", test_func17},
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
