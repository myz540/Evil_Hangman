/*

Unit test driver, requires the my_string module and unit_test header files to run

*/

#include "my_string.h"
#include "unit_test.h"

int main(int argc, char* argv[])
{
	Status(*tests[])(char*, int) =
	{
		MZ_test_init_default_returns_nonNULL,
		MZ_test_get_size_on_init_default_returns_0,
		MZ_test_get_capacity_on_init_default_returns_8,
		MZ_test_init_c_str_returns_nonNULL,
		MZ_test_get_size_on_init_c_str_returns_correct,
		MZ_test_get_capacity_on_init_c_str_returns_correct,
		MZ_test_destroy_handle_points_to_NULL,
		MZ_test_pushback_non_full_increases_size,
		MZ_test_pushback_non_full_stores_char,
		MZ_test_pushback_full_increases_capacity,
		MZ_test_pushback_full_increases_size,
		MZ_test_pushback_full_stores_char,
		MZ_test_at_returns_NULL_given_empty_vector,
		MZ_test_at_returns_NULL_given_invalid_index,
		MZ_test_at_returns_correct_characters_after_pushback,
		MZ_test_popback_reduces_size_by_1,
		MZ_test_popback_returns_FAILURE_on_empty_vector,
		MZ_test_compare_returns_0_given_same_strings,
		MZ_test_compare_returns_1_given_different_size_strings,
		MZ_test_compare_returns_1_given_different_strings_of_same_size,
		MZ_test_c_string_returns_NULL_terminated_string,
		MZ_test_c_string_resizes_full_string_to_append_NULL_terminator,
		MZ_test_concatenate_returns_correct_size_of_destination,
		MZ_test_concatenate_properly_resizes_destination_when_full,
		//JEREMY
		test_init_default_returns_nonNULL,
		test_get_size_on_init_default_returns_0,
		test_get_capacity_on_init_default_returns_8,
		test_destroy_returns_null,
		test_string_compare_returns_neg_one_when_string1_is_smaller,
		test_string_compare_returns_0_when_strings_are_equal,
		test_string_compare_returns_1_when_string1_is_greater,
		test_init_c_str_capacity_equals_word_size,
		test_push_back_doubles_capacity_of_c_str_as_needed,
		test_push_back_doubles_capacity_of_default_str_as_needed,
		test_pop_back_removes_a_single_element_per_iteration,
		test_pop_back_returns_failure_when_size_0,
		test_pop_back_size_decrease,
		test_at_returns_the_correct_element,
		test_at_cannot_return_an_element_that_is_out_of_range,
		test_concatenate_creates_enough_space_to_combine_characters,
		test_concatenate_combines_two_strings_in_the_correct_order,
		test_c_str_changes_a_character_array_into_a_c_str,
		test_c_str_returns_char_ptr_not_a_char_value,
		//BRETT
		test_init_default_returns_nonNULL,
		test_init_default_capacity_greater_than_size,
		test_init_default_capacity_more_than0,
		test_destroy_function,
		test_push_function,
		test_push_size_resizing,
		test_push_capacity_resizing,
		test_init_c_str_takes_string,
		test_string_compare_equal,
		test_string_compare_greater_than,
		test_string_compare_less_than,
		test_at_function,
		test_at_return_NULL,
		test_init_get_size_function,
		test_pop_resizing,
		test_pop_return_fail,
		test_extraction_function,
		test_concat_function,
		test_concat_size_resize,
		test_concat_capacity_resize,
		test_c_str_function,
		test_c_str_capacity_resize,
		//ANTHONY
		AB_test_1_init,
		AB_test_2_destroy,
		AB_test_3_get_size,
		AB_test_4_get_capacity,
		AB_test_5_pop_back_returns_status,
		AB_test_6_push_back_returns_status,
		AB_test_7_push_back_changes_size,
		AB_test_8_pop_back_changes_size,
		AB_test_10_at_returns_null_out_of_limits,
		AB_test_11_at_returns_address_of_char_in_index,
		AB_test_12_string_compare_same_returns_0,
		AB_test_13_string_compare_returns_negative_if_first_comes_before,
		AB_test_14_string_compare_returns_positive_if_first_comes_after,
		AB_test_15_init_c_string,
		AB_test_16_concat,
		AB_test_17_extraction_on_empty_fails,
		AB_test_18_extraction_on_white_spaces_contains_NULL,
		AB_test_19_extraction_gets_one_word_from_file,
		AB_test_20_string_at_capacity_resizes_for_c_str_but_does_not_change_size,
		AB_test_21_extraction_can_skip_white_space,
		AB_test_22_destroying_a_non_exisiting_handle_does_not_crash_program,
		AB_test_23_string_ing_strings,
		AB_test_24_init_empty_str_force_pop_off_of_nothing,
		AB_test_25_read_through_large_doc_successfully_stopping_at_end,
		AB_test_26_compare_strings_does_not_account_for_less_length,
		AB_test_27_compare_strings_does_not_account_for_more_length,
		AB_test_28_compare_strings_does_not_account_for_capitol_letters
	};

	int number_of_functions = sizeof(tests) / sizeof(tests[0]);
	int i, pass = 0, fail = 0;
	char buffer[500];

	for (i = 0; i < number_of_functions; i++){
		if (tests[i](buffer, 500) == FAILURE){
			printf("\nFAILED: Test %d failed\n", i);
			printf("\t%s\n", buffer);
			fail++;
		}
		else{
			printf("\nPASSED: Test %d passed\n", i);
			printf("\t%s\n", buffer);
			pass++;
		}
	}
	printf("\nThe number of functions in MZ unit test is %d\n", number_of_functions);
	printf("Passed %d/%d and failed %d/%d\n", pass, number_of_functions, fail, number_of_functions);

	return 0;
}
