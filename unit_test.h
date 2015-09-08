/*

Header file for unit test driver

*/

#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include "my_string.h"
//MIKE ZHONG
Status MZ_test_init_default_returns_nonNULL(char* buffer, int length);
Status MZ_test_get_size_on_init_default_returns_0(char* buffer, int length);
Status MZ_test_get_capacity_on_init_default_returns_8(char* buffer, int length);
Status MZ_test_init_c_str_returns_nonNULL(char* buffer, int length);
Status MZ_test_get_size_on_init_c_str_returns_correct(char* buffer, int length);
Status MZ_test_get_capacity_on_init_c_str_returns_correct(char* buffer, int length);
Status MZ_test_destroy_handle_points_to_NULL(char* buffer, int length);
Status MZ_test_pushback_non_full_increases_size(char* buffer, int length);
Status MZ_test_pushback_non_full_stores_char(char* buffer, int length);
Status MZ_test_pushback_full_increases_capacity(char* buffer, int length);
Status MZ_test_pushback_full_increases_size(char* buffer, int length);
Status MZ_test_pushback_full_stores_char(char* buffer, int length);
Status MZ_test_at_returns_NULL_given_empty_vector(char* buffer, int length);
Status MZ_test_at_returns_NULL_given_invalid_index(char* buffer, int length);
Status MZ_test_at_returns_correct_characters_after_pushback(char* buffer, int length);
Status MZ_test_popback_reduces_size_by_1(char* buffer, int length);
Status MZ_test_popback_returns_FAILURE_on_empty_vector(char*buffer, int length);
Status MZ_test_compare_returns_0_given_same_strings(char* buffer, int length);
Status MZ_test_compare_returns_1_given_different_size_strings(char* buffer, int length);
Status MZ_test_compare_returns_1_given_different_strings_of_same_size(char* buffer, int length);
Status MZ_test_c_string_returns_NULL_terminated_string(char* buffer, int length);
Status MZ_test_c_string_resizes_full_string_to_append_NULL_terminator(char* buffer, int length);
Status MZ_test_concatenate_returns_correct_size_of_destination(char* buffer, int length);
Status MZ_test_concatenate_properly_resizes_destination_when_full(char* buffer, int length);
//JEREMY
Status test_init_default_returns_nonNULL(char* buffer, int length);
Status test_get_size_on_init_default_returns_0(char* buffer, int length);
Status test_get_capacity_on_init_default_returns_8(char*buffer, int length);
Status test_destroy_returns_null(char* buffer, int length);
Status test_string_compare_returns_neg_one_when_string1_is_smaller(char* buffer, int length);
Status test_string_compare_returns_0_when_strings_are_equal(char* buffer, int length);
Status test_string_compare_returns_1_when_string1_is_greater(char* buffer, int length);
Status test_init_c_str_capacity_equals_word_size(char* buffer, int length);
Status test_push_back_doubles_capacity_of_c_str_as_needed(char* buffer, int length);
Status test_push_back_doubles_capacity_of_default_str_as_needed(char* buffer, int length);
Status test_pop_back_removes_a_single_element_per_iteration(char* buffer, int length);
Status test_pop_back_returns_failure_when_size_0(char* buffer, int length);
Status test_pop_back_size_decrease(char* buffer, int length);
Status test_at_returns_the_correct_element(char* buffer, int length);
Status test_at_cannot_return_an_element_that_is_out_of_range(char* buffer, int length);
Status test_concatenate_creates_enough_space_to_combine_characters(char* buffer, int length);
Status test_concatenate_combines_two_strings_in_the_correct_order(char* buffer, int length);
Status test_c_str_changes_a_character_array_into_a_c_str(char* buffer, int length);
Status test_c_str_returns_char_ptr_not_a_char_value(char* buffer, int length);
//BRETT
Status test_init_default_capacity_greater_than_size(char* buffer, int length);
Status test_init_default_capacity_more_than0(char* buffer, int length);
Status test_destroy_function(char* buffer, int length);
Status test_push_function(char* buffer, int length);
Status test_push_size_resizing(char* buffer, int length);
Status test_push_capacity_resizing(char* buffer, int length);
Status test_init_c_str_takes_string(char* buffer, int length);
Status test_string_compare_equal(char* buffer, int length);
Status test_string_compare_greater_than(char* buffer, int length);
Status test_string_compare_less_than(char* buffer, int length);
Status test_at_function(char* buffer, int length);
Status test_at_return_NULL(char* buffer, int length);
Status test_init_get_size_function(char* buffer, int length);
Status test_pop_resizing(char* buffer, int length);
Status test_pop_return_fail(char* buffer, int length);
Status test_extraction_function(char* buffer, int length);
Status test_concat_function(char* buffer, int length);
Status test_concat_size_resize(char* buffer, int length);
Status test_concat_capacity_resize(char* buffer, int length);
Status test_c_str_function(char* buffer, int length);
Status test_c_str_capacity_resize(char* buffer, int length);
//ANTHONY
Status AB_test_1_init(char* buffer, int length);
Status AB_test_2_destroy(char* buffer, int length);
Status AB_test_3_get_size(char* buffer, int length);
Status AB_test_4_get_capacity(char* buffer, int length);
Status AB_test_5_pop_back_returns_status(char* buffer, int length);
Status AB_test_6_push_back_returns_status(char* buffer, int length);
Status AB_test_7_push_back_changes_size(char* buffer, int length);
Status AB_test_8_pop_back_changes_size(char* buffer, int length);
Status AB_test_10_at_returns_null_out_of_limits(char* buffer, int length);
Status AB_test_11_at_returns_address_of_char_in_index(char* buffer, int length);
Status AB_test_12_string_compare_same_returns_0(char* buffer, int length);
Status AB_test_13_string_compare_returns_negative_if_first_comes_before(char* buffer, int length);
Status AB_test_14_string_compare_returns_positive_if_first_comes_after(char* buffer, int length);
Status AB_test_15_init_c_string(char* buffer, int length);
Status AB_test_16_concat(char* buffer, int length);
Status AB_test_17_extraction_on_empty_fails(char* buffer, int length);
Status AB_test_18_extraction_on_white_spaces_contains_NULL(char* buffer, int length);
Status AB_test_19_extraction_gets_one_word_from_file(char* buffer, int length);
Status AB_test_20_string_at_capacity_resizes_for_c_str_but_does_not_change_size(char* buffer, int length);
Status AB_test_21_extraction_can_skip_white_space(char* buffer, int length);
Status AB_test_22_destroying_a_non_exisiting_handle_does_not_crash_program(char* buffer, int length);
Status AB_test_23_string_ing_strings(char* buffer, int length);
Status AB_test_24_init_empty_str_force_pop_off_of_nothing(char* buffer, int length);
Status AB_test_25_read_through_large_doc_successfully_stopping_at_end(char* buffer, int length);
Status AB_test_26_compare_strings_does_not_account_for_less_length(char* buffer, int length);
Status AB_test_27_compare_strings_does_not_account_for_more_length(char* buffer, int length);
Status AB_test_28_compare_strings_does_not_account_for_capitol_letters(char* buffer, int length);



#endif
