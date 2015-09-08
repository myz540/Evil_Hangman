/* 

This file contains all the test definitions for the unit test driver

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unit_test.h"
#include "my_string.h"

Status MZ_test_init_default_returns_nonNULL(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;

	hString = my_string_init_default();

	if (hString == NULL){
		strncpy(buffer, "my_string_init_default returns NULL", length);
		status = FAILURE;
	}
	else{
		hString->destroy(&hString);
		strncpy(buffer, "my_string_init_default returns non-Null", length);
		status = SUCCESS;
	}
	return status;
}

Status MZ_test_get_size_on_init_default_returns_0(char* buffer, int length)
{
	MY_STRING hString = my_string_init_default();
	Status status;

	if (hString->get_size(hString) != 0){
		status = FAILURE;
		printf("Expected a size of 0, but got %d\n", hString->get_size(hString));
		strncpy(buffer, "my_string_init_default did not receive 0 from get_size function", length);
	}
	else{
		status = SUCCESS;
		strncpy(buffer, "my_string_init_default receives 0 from get_size function", length);
	}
	hString->destroy(&hString);
	return status;
}

Status MZ_test_get_capacity_on_init_default_returns_8(char* buffer, int length)
{
	MY_STRING hString = my_string_init_default();
	Status status;

	if (hString->get_capacity(hString) != 8){
		status = FAILURE;
		printf("Expected a capacity of 8, but got %d\n", hString->get_capacity(hString));
		hString->get_capacity(hString);
		strncpy(buffer, "my_sting_init_default did not receive 0 from get_capacity function", length);
	}
	else{
		status = SUCCESS;
		strncpy(buffer, "my_string_init_default receives 8 from get_capacity function", length);
	}
	hString->destroy(&hString);
	return status;
}

Status MZ_test_init_c_str_returns_nonNULL(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;

	hString = my_string_init_c_str("Test");
	if (hString == NULL){
		status = FAILURE;
		strncpy(buffer, "my_string_init_c_str returns NULL given a test case", length);
	}
	else{
		status = SUCCESS;
		strncpy(buffer, "my_string_init_c_str returns non-NULL given a test case", length);
		hString->destroy(&hString);
	}
	return status;
}
Status MZ_test_get_size_on_init_c_str_returns_correct(char* buffer, int length)
{
	MY_STRING hString = my_string_init_c_str("Test");
	Status status;

	if (hString->get_size(hString) == 4){
		status = SUCCESS;
		strncpy(buffer, "get_size on my_string_init_c_str with a test case\n"
			"\treturns the correct size of the string", length);
	}
	else{
		status = FAILURE;
		strncpy(buffer, "get_size on my_string_init_c_str does not return the correct size", length);
	}
	hString->destroy(&hString);
	return status;
}

Status MZ_test_get_capacity_on_init_c_str_returns_correct(char* buffer, int length)
{
	MY_STRING hString = my_string_init_c_str("Test");
	Status status;

	if (hString->get_capacity(hString) == 5){
		status = SUCCESS;
		strncpy(buffer, "get_capacity on my_string_init_c_str with a test case\n"
			"\treturns the correct capacity of the string", length);
	}
	else{
		status = FAILURE;
		strncpy(buffer, "get_capacity on my_string_init_c_str does\n"
			"\tnot return the correct capacity", length);
	}
	hString->destroy(&hString);
	return status;
}

Status MZ_test_destroy_handle_points_to_NULL(char* buffer, int length)
{
	MY_STRING hString = my_string_init_default();
	Status status;

	hString->destroy(&hString);

	if (hString != NULL){
		status = FAILURE;
		strncpy(buffer, "my_string_destroy has not set either the handle to My_string to NULL", length);
	}
	else{
		status = SUCCESS;
		strncpy(buffer, "my_string_destroy has deallocated the memory (allegedly)\n"
			"\tand set the handle to NULL", length);
	}
	return status;
}

Status MZ_test_pushback_non_full_increases_size(char* buffer, int length)
{
	MY_STRING hString = my_string_init_default();
	Status status;

	hString->push_back(hString, 't');

	if (hString->get_size(hString) == 1){
		status = SUCCESS;
		strncpy(buffer, "my_string_pushback has successfully inserted a character\n"
			"\tand increased the size to 1 for a vector not at capacity", length);
	}
	else{
		status = FAILURE;
		strncpy(buffer, "my_string_pushback has failed to increase the size of the vector", length);
	}
	hString->destroy(&hString);
	return status;
}

Status MZ_test_pushback_non_full_stores_char(char* buffer, int length)
{
	MY_STRING hString = my_string_init_default();
	Status status;

	hString->push_back(hString, 'T');
	hString->push_back(hString, 'e');

	if (*hString->at(hString, 0) == 'T' && *hString->at(hString, 1) == 'e'){
		status = SUCCESS;
		strncpy(buffer, "my_string_pushback successfully stores\n"
			"\tcorrect character at the correct index", length);
	}
	else{
		status = FAILURE;
		strncpy(buffer, "my_string_pushback fails to store correct character", length);
	}
	hString->destroy(&hString);
	return status;
}

Status MZ_test_pushback_full_increases_capacity(char* buffer, int length)
{
	MY_STRING hString = my_string_init_default();
	Status status;
	int i, before, after;

	for (i = 0; i < hString->get_capacity(hString); i++){
		hString->push_back(hString, 'T');
	}

	before = hString->get_capacity(hString);
	hString->push_back(hString, 'T');
	after = hString->get_capacity(hString);

	if (before == 8 && after == 16){
		status = SUCCESS;
		strncpy(buffer, "my_string_pushback on a vector at capacity successfully doubles\n"
			"\tthe capacity", length);
	}
	else{
		status = SUCCESS;
		strncpy(buffer, "my_string_pushback on a vector at capacity failed to double\n"
			"\tthe original capacity", length);
	}
	hString->destroy(&hString);
	return status;
}

Status MZ_test_pushback_full_increases_size(char* buffer, int length)
{
	MY_STRING hString = my_string_init_default();
	Status status;
	int i, before, after;

	for (i = 0; i < hString->get_capacity(hString); i++){
		hString->push_back(hString, 'T');
	}

	before = hString->get_size(hString);
	hString->push_back(hString, 'T');
	after = hString->get_size(hString);

	if (before == 8 && after == 9){
		status = SUCCESS;
		strncpy(buffer, "my_string_pushback on a vector at capacity successfully\n"
			"\tincrements the size by 1", length);
	}
	else{
		status = FAILURE;
		strncpy(buffer, "my_string_pushback on a vector at capacity fails to\n"
			"\tincrement the size by 1", length);
	}
	hString->destroy(&hString);
	return status;
}

Status MZ_test_pushback_full_stores_char(char* buffer, int length)
{
	MY_STRING hString = my_string_init_default();
	Status status;
	int i;

	for (i = 0; i < hString->get_capacity(hString); i++){
		hString->push_back(hString, 'T');
	}

	hString->push_back(hString, 'e');

	if (*hString->at(hString, 8) == 'e'){
		status = SUCCESS;
		strncpy(buffer, "my_string_pushback on a vector at capacity successfully\n"
			"\tstores the character in the newly created array", length);
	}
	else{
		status = FAILURE;
		strncpy(buffer, "my_string_pushback on a vector at capacity fails to\n"
			"\tstore the character in the newly created array", length);
	}
	hString->destroy(&hString);
	return status;
}

Status MZ_test_at_returns_NULL_given_empty_vector(char* buffer, int length)
{
	MY_STRING hString = my_string_init_default();
	Status status;

	if (hString->at(hString, 0) == NULL && hString->get_size(hString) == 0){
		status = SUCCESS;
		strncpy(buffer, "my_string_at returns NULL when given an empty vector", length);
	}
	else{
		status = FAILURE;
		printf("Expected NULL, instead got '%c'\n", *hString->at(hString, 0));
		strncpy(buffer, "my_string_at did not return NULL when given an empty vector", length);
	}
	hString->destroy(&hString);
	return status;
}

Status MZ_test_at_returns_NULL_given_invalid_index(char* buffer, int length)
{
	MY_STRING hString = my_string_init_default();
	Status status;

	hString->push_back(hString, 'C');

	if (hString->at(hString, 1) != NULL){
		status = FAILURE;
		printf("Expected NULL, but instead got '%c'\n", *hString->at(hString, 1));
		strncpy(buffer, "my_string_at did not return NULL when given an invalid index", length);
	}
	else{
		status = SUCCESS;
		strncpy(buffer, "my_string_at returns NULL given an invalid index", length);
	}
	hString->destroy(&hString);
	return status;
}

Status MZ_test_at_returns_correct_characters_after_pushback(char* buffer, int length)
{
	MY_STRING hString = my_string_init_default();
	Status status;

	hString->push_back(hString, 'T');
	hString->push_back(hString, 'e');
	hString->push_back(hString, 's');
	hString->push_back(hString, 't');

	if (*hString->at(hString, 0) == 'T' && *hString->at(hString, 1) == 'e' &&
		*hString->at(hString, 2) == 's' && *hString->at(hString, 3) == 't'){
		status = SUCCESS;
		strncpy(buffer, "my_string_at returns the correct character after a\n"
			"\tseries of pushback operations", length);
	}
	else{
		status = FAILURE;
		printf("expected char 'T' 'e' 's' 't' but instead,\n"
			"\t my_string_at returned '%c' '%c' '%c' '%c'\n",
			*hString->at(hString, 0), *hString->at(hString, 1),
			*hString->at(hString, 2), *hString->at(hString, 3));
		strncpy(buffer, "my_string_at did not return the corrent character", length);
	}
	hString->destroy(&hString);
	return status;
}

Status MZ_test_popback_reduces_size_by_1(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	int before, after;

	hString = my_string_init_default();

	hString->push_back(hString, 'c');
	before = hString->get_size(hString);

	hString->pop_back(hString);
	after = hString->get_size(hString);

	if (before == after + 1){
		status = SUCCESS;
		strncpy(buffer, "my_string_popback has successfully decremented the size by 1", length);
	}
	else{
		status = FAILURE;
		printf("The size before is %d, and after the popback, the size is %d\n", before, after);
		strncpy(buffer, "my_string_popback has not decremented the size", length);
	}
	hString->destroy(&hString);
	return status;
}

Status MZ_test_popback_returns_FAILURE_on_empty_vector(char*buffer, int length)
{
	MY_STRING hString = my_string_init_default();
	Status status;

	if (hString->pop_back(hString) == FAILURE){
		status = SUCCESS;
		strncpy(buffer, "my_string_popback successfully returns FAILURE when given\n"
			"\tan empty vector immediately after initialization", length);
	}
	else{
		status = FAILURE;
		strncpy(buffer, "my_string_popback returns a value other than FAILURE when given\n"
			"\tan empty vector immediately after initialization", length);
	}
	hString->destroy(&hString);
	return status;
}

Status MZ_test_compare_returns_0_given_same_strings(char* buffer, int length)
{
	MY_STRING hString1 = my_string_init_c_str("Test");
	MY_STRING hString2 = my_string_init_c_str("Test");
	Status status;

	if (hString1->string_compare(hString1, hString2) == 0){
		status = SUCCESS;
		strncpy(buffer, "my_string_compare returns 0 given two identical test strings", length);
	}
	else{
		status = FAILURE;
		strncpy(buffer, "my_string_compare fails to return 0 given two identical test strings", length);
	}
	hString1->destroy(&hString1);
	hString2->destroy(&hString2);
	return status;
}

Status MZ_test_compare_returns_1_given_different_size_strings(char* buffer, int length)
{
	MY_STRING hString1 = my_string_init_c_str("Testing");
	MY_STRING hString2 = my_string_init_c_str("Test");
	Status status;

	if (hString1->string_compare(hString1, hString2) == 1){
		status = SUCCESS;
		strncpy(buffer, "my_string_compare returns 1 given two test strings of different\n"
			"\tlength, where string1 > string2 in size, while all other chars match", length);
	}
	else{
		status = FAILURE;
		strncpy(buffer, "my_string_compare fails to return 1 given two test strings\n"
			"\tof different length, where string 1 > string 2 in size", length);
	}
	hString1->destroy(&hString1);
	hString2->destroy(&hString2);
	return status;
}

Status MZ_test_compare_returns_1_given_different_strings_of_same_size(char* buffer, int length)
{
	MY_STRING hString1 = my_string_init_c_str("TEST");
	MY_STRING hString2 = my_string_init_c_str("TESS");
	Status status;

	if (hString1->string_compare(hString1, hString2) == 1){
		status = SUCCESS;
		strncpy(buffer, "my_string_compare returns 1 given two different test strings\n"
			"\tof the same size, differing on the final character", length);
	}
	else{
		status = FAILURE;
		strncpy(buffer, "my_string_compare fails to return 1 given two different test strings\n"
			"\tof the same size, differing on the final character", length);
	}
	hString1->destroy(&hString1);
	hString2->destroy(&hString2);
	return status;
}

Status MZ_test_c_string_returns_NULL_terminated_string(char* buffer, int length)
{
	MY_STRING hString = my_string_init_c_str("TEST");
	Status status;
	char* check_terminator;

	check_terminator = hString->c_str(hString);

	if (check_terminator[hString->get_size(hString)] == '\0'){
		status = SUCCESS;
		strncpy(buffer, "my_c_string returns a null terminated string at index size\n"
			"\tgiven a test string", length);
	}
	else{
		status = FAILURE;
		strncpy(buffer, "my_c_string fails to return a null terminated string\n"
			"\tgiven a test string", length);
	}
	hString->destroy(&hString);
	return status;
}

Status MZ_test_c_string_resizes_full_string_to_append_NULL_terminator(char* buffer, int length)
{
	MY_STRING hString = my_string_init_default();
	Status status;
	int i, before, after;
	char* check_terminator;

	for (i = 0; i < hString->get_capacity(hString); i++){
		hString->push_back(hString, 'T');
	}

	before = hString->get_capacity(hString);
	check_terminator = hString->c_str(hString);
	after = hString->get_capacity(hString);

	if (before == 8 && after == 16 && check_terminator[hString->get_size(hString)] == 0){
		status = SUCCESS;
		strncpy(buffer, "my_c_string successfully resizes a full string to double its original\n"
			"\tcapacity and appends the null terminator at index size of hString", length);
	}
	else{
		status = FAILURE;
		strncpy(buffer, "my_c_string has failed to resize a full string. Either the original\n"
			"\tcapacity, the new capacity, or the null terminator are wrong", length);
	}
	hString->destroy(&hString);
	return status;
}

Status MZ_test_concatenate_returns_correct_size_of_destination(char* buffer, int length)
{
	MY_STRING destination = my_string_init_c_str("TE");
	MY_STRING add = my_string_init_c_str("ST");
	int before, after;
	Status status;

	before = destination->get_size(destination);
	if (destination->concat(destination, add) == SUCCESS){
		after = destination->get_size(destination);
		if (before == 2 && after == 4){
			status = SUCCESS;
			strncpy(buffer, "my_string_concatenate returns SUCCESS and properly changes\n"
				"\tthe destination string to its new size", length);
		}
		else{
			status = FAILURE;
			strncpy(buffer, "my_string_concatenate FAILED to properly change\n"
				"\tthe destination string to its new size", length);
		}
	}
	else{
		status = FAILURE;
		strncpy(buffer, "my_string_concatenate returned FAILURE, need further diagnostic testing", length);
	}
	destination->destroy(&destination);
	return status;
}

Status MZ_test_concatenate_properly_resizes_destination_when_full(char* buffer, int length)
{
	MY_STRING destination = my_string_init_c_str("TE");
	MY_STRING add = my_string_init_c_str("ST");
	Status status;
	int before, after;

	before = destination->get_capacity(destination);
	destination->concat(destination, add);
	after = destination->get_capacity(destination);

	if (before == 3 && after == 6){
		status = SUCCESS;
		strncpy(buffer, "my_string_concatenate properly resizes the destination string according\n"
			"\tto the pushback function's definition. The new capacity is double\n"
			"\tthe capacityof the original string", length);
	}
	else{
		status = FAILURE;
		strncpy(buffer, "my_string_concatenate faile to resize the destination string when\n"
			"\tit ran out of space during the appending of the add string", length);
	}
	destination->destroy(&destination);
	return status;
}

//JEREMY

Status test_init_default_returns_nonNULL(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;

	hString = my_string_init_default();

	if (hString == NULL)
	{
		status = FAILURE;
		strncpy(buffer, "test_init_default returns nonNULL\n"
			"\tmy_string_init_default returns NULL\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_init_default_returns_nonNULL\n", length);
	}
	hString->destroy(&hString);
	return status;
}

Status test_get_size_on_init_default_returns_0(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;

	hString = my_string_init_default();

	if (hString->get_size(hString) != 0)
	{
		status = FAILURE;
		printf("Expected a size of 0 but got %d\n", hString->get_size(hString));
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
			"\tDid not receive 0 from get_size after init_default\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n", length);
	}
	hString->destroy(&hString);
	return status;
}

Status test_get_capacity_on_init_default_returns_8(char* buffer, int length){
	MY_STRING hString = NULL;
	Status status;
	int capacity;

	hString = my_string_init_default();

	capacity = hString->get_capacity(hString);

	if (capacity != 8)
	{
		status = FAILURE;
		printf("Expected a size of 8 but got %d\n", capacity);
		strncpy(buffer, "test_get_capacity_on_init_default_returns_8\n"
			"\tDid not receive 8 from get_capacity after init_default\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_get_capacity_on_init_default_returns_8\n", length);
	}
	hString->destroy(&hString);
	return status;
}

Status test_destroy_returns_null(char* buffer, int length)
{
	MY_STRING hString = my_string_init_default();
	Status status;

	hString->destroy(&hString);

	if (hString == NULL)
	{
		status = SUCCESS;
		strncpy(buffer, "test_destroy_returns_null\n", length);
	}
	else
	{
		status = FAILURE;
		printf("Destroy function ineffective, memory leak likely\n");
		strncpy(buffer, "test_destroy_returns_null\n"
			"\tThe pointer still contains the address of the freed space", length);
	}
	return status;
}

Status test_string_compare_returns_neg_one_when_string1_is_smaller(char* buffer, int length)
{
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	Status status;

	hString1 = my_string_init_c_str("Test");
	hString2 = my_string_init_c_str("Test1");

	if (hString1->string_compare(hString1, hString2) != -1)
	{
		status = FAILURE;
		printf("Expected string1 to be smaller\n");
		strncpy(buffer, "test_string_compare_returns_neg_one_when_string1_is_smaller\n"
			"\tDid not return -1 when String1 was smaller than String2\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_string_compare_returns_neg_one_when_string1_is_smaller\n", length);
	}
	hString1->destroy(&hString1); hString2->destroy(&hString2);
	return status;
}

Status test_string_compare_returns_0_when_strings_are_equal(char* buffer, int length)
{
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	Status status;

	hString1 = my_string_init_c_str("Test1");
	hString2 = my_string_init_c_str("Test1");

	if (hString1->string_compare(hString1, hString2) != 0)
	{
		status = FAILURE;
		printf("Expected strings to be equal\n");
		strncpy(buffer, "test_string_compare_returns_0_when_strings_are_equal\n"
			"\tDid not return 0 when String1 was equal to String2\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_string_compare_returns_0_when_strings_are_equal\n", length);
	}
	hString1->destroy(&hString1); hString2->destroy(&hString2);
	return status;
}

Status test_string_compare_returns_1_when_string1_is_greater(char* buffer, int length)
{
	MY_STRING hString1 = NULL;
	MY_STRING hString2 = NULL;
	Status status;

	hString1 = my_string_init_c_str("Test1");
	hString2 = my_string_init_c_str("Test");

	if (hString1->string_compare(hString1, hString2) != 1)
	{
		status = FAILURE;
		printf("Expected string1 to be larger\n");
		strncpy(buffer, "test_string_compare_returns_1_when_string1_is_greater\n"
			"\tDid not return 1 when String1 was larger than String2\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_string_compare_returns_1_when_string1_is_greater\n", length);
	}
	hString1->destroy(&hString1); hString2->destroy(&hString2);
	return status;
}

Status test_init_c_str_capacity_equals_word_size(char* buffer, int length)
{
	MY_STRING hString = my_string_init_c_str("test1");
	Status status;
	int capacity;

	capacity = hString->get_capacity(hString);
	if (capacity < 5)
	{
		status = FAILURE;
		printf("Given a string of 5 characters, capacity should have been 5, but instead was %d\n", capacity);
		strncpy(buffer, "test_init_c_str_capacity_equals_word_size\n"
			"\tCapacity was incorrect for the length of the string given.\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_init_c_str_capacity_equals_word_size\n", length);
	}
	return status;
}

Status test_push_back_doubles_capacity_of_c_str_as_needed(char* buffer, int length)
{
	Status status;
	MY_STRING hString = my_string_init_c_str("testing");
	int capacity;

	hString->push_back(hString, 'a');
	hString->push_back(hString, 'a');

	capacity = hString->get_capacity(hString);

	if (capacity != 16)
	{
		status = FAILURE;
		printf("Given a c_str 7 characters long, expected capacity to double to 14, but it was instead: %d\n", capacity);
		strncpy(buffer, "test_push_back_doubles_capacity_when_added_to_a_c_str\n"
			"\tPush function did not properly change the capacity\n", length);
	}
	else
	{
		hString->push_back(hString, 'a');
	

		capacity = hString->get_capacity(hString);
		if (capacity != 16)
		{
			status = FAILURE;
			printf("While capacity was at 14, pushing on a character to a string of size 8 caused capacity to change\n");
			strncpy(buffer, "test_push_back_doubles_capacity_when_added_to_a_c_str\n"
				"\tPush function did not properly change the capacity\n", length);
		}
		else
		{
			status = SUCCESS;
			strncpy(buffer, "test_push_back_doubles_capacity_when_added_to_a_c_str\n", length);
		}
	}
	hString->destroy(&hString);
	return status;
}

Status test_push_back_doubles_capacity_of_default_str_as_needed(char* buffer, int length)
{
	Status status;
	int start_cap, index;
	MY_STRING hString;

	hString = my_string_init_default();
	start_cap = hString->get_capacity(hString);

	for (index = 0; index < start_cap; index++)
	{
		hString->push_back(hString, 'a');
	}
	if (hString->get_capacity(hString) != start_cap)
	{
		status = FAILURE;
		printf("Push function changed capacity before it was supposed to\n");
		strncpy(buffer, "test_push_back_doubles_capacity_of_default_str_as_needed\n"
			"\tPush function did not properly change the capacity\n", length);
	}
	else
	{
		hString->push_back(hString, 'a');
		if (hString->get_capacity(hString) != start_cap * 2)
		{
			status = FAILURE;
			printf("Push function did not change capacity when needed\n");
			strncpy(buffer, "test_push_back_doubles_capacity_of_default_str_as_needed\n"
				"\tPush function did not properly change the capacity\n", length);
		}
		else
		{
			status = SUCCESS;
			strncpy(buffer, "test_push_back_doubles_capacity_of_default_str_as_needed\n", length);
		}
	}
	hString->destroy(&hString);
	return status;
}

Status test_pop_back_removes_a_single_element_per_iteration(char* buffer, int length)
{
	Status status;
	int size;
	MY_STRING hString;
	hString = my_string_init_c_str("Test1");

	size = hString->get_size(hString);

	hString->pop_back(hString);

	/*size -1 for the correct index, and -1 for the removed element*/
	if (*hString->at(hString, size - 2) != 't')
	{
		status = FAILURE;
		printf("Given the string 'Test1', the last element after pop back should be 't' but was not\n");
		strncpy(buffer, "test_pop_back_removes_a_single_element_per_iteration\n"
			"\tPop function does not remove elements from the given string correctly\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_pop_back_removes_a_single_element_per_iteration\n", length);
	}
	hString->destroy(&hString);
	return status;
}

Status test_pop_back_returns_failure_when_size_0(char* buffer, int length)
{
	MY_STRING hString = my_string_init_default();
	Status status, test;

	test = hString->pop_back(hString);
	if (test == FAILURE)
	{
		status = SUCCESS;
		strncpy(buffer, "test_pop_back_returns_failure_when_size_0\n", length);
	}
	else
	{
		status = FAILURE;
		printf("Pop_back does not fail when size is equal to zero\n");
		strncpy(buffer, "test_pop_back_returns_failure_when_size_0\n"
			"\tpop_back does not fail when necessary", length);
	}
	return status;
}

Status test_pop_back_size_decrease(char* buffer, int length)
{
	MY_STRING hString = my_string_init_c_str("Test1");
	Status status;
	int number;

	number = hString->get_size(hString);
	hString->pop_back(hString);
	if (hString->get_size(hString) == (number - 1))
	{
		status = SUCCESS;
		strncpy(buffer, "test_pop_back_size_decrease\n", length);
	}
	else
	{
		status = FAILURE;
		printf("Pop_back fails to decrease the size of the vector\n");
		strncpy(buffer, "test_pop_back_size_decrease\n"
			"\tpop_back did not successfully decrease size", length);
	}
	hString->destroy(&hString);
	return status;
}

Status test_at_returns_the_correct_element(char* buffer, int length)
{
	Status status;
	int i;
	char alpha[] = "abc";
	MY_STRING hString;

	hString = my_string_init_c_str("abc");

	for (i = 0; i < 3 && *hString->at(hString, i) == alpha[i]; i++);

	if (i == 3)
	{
		status = SUCCESS;
		strncpy(buffer, "test_at_returns_the_correct_element\n", length);
	}
	else
	{
		status = FAILURE;
		printf("Given the string 'abc', the at function did not correctly return each element\n");
		strncpy(buffer, "test_at_returns_the_correct_element\n"
			"\tThe at function does not correctly return the requested element\n", length);
	}
	hString->destroy(&hString);
	return status;
}

Status test_at_cannot_return_an_element_that_is_out_of_range(char* buffer, int length)
{
	Status status;
	int i;
	MY_STRING hString;

	hString = my_string_init_c_str("Test1");

	i = hString->get_size(hString);

	if (hString->at(hString, i) != NULL)
	{
		status = FAILURE;
		printf("At function attempted to return the value within an element that was out of range rather than NULL\n");
		strncpy(buffer, "test_at_cannot_return_an_element_that_is_out_of_range\n"
			"\tThe at function does not correctly handle requests that are out of range\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_at_cannot_return_an_element_that_is_out_of_range\n", length);
	}
	hString->destroy(&hString);
	return status;
}

Status test_concatenate_creates_enough_space_to_combine_characters(char* buffer, int length)
{
	Status status;
	int size;
	char concat[] = "Test String";
	MY_STRING hString1, hString2;

	hString1 = my_string_init_c_str("Test");
	hString2 = my_string_init_c_str("String");

	size = (hString1->get_size(hString1) + hString2->get_size(hString2) + 1);

	hString1->concat(hString1, hString2);

	if (size < hString1->get_size(hString1))
	{
		status = FAILURE;
		printf("Concatenate function failed to create enough space to combine the two strings\n");
		strncpy(buffer, "test_concatenate_creates_enough_space_to_combine_characters\n"
			"Concatenate function does not properly allocate additional space\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_concatenate_creates_enough_space_to_combine_characters\n", length);
	}

	hString1->destroy(&hString1);
	hString2->destroy(&hString2);
	return status;
}

Status test_concatenate_combines_two_strings_in_the_correct_order(char* buffer, int length)
{
	Status status;
	int i, size;
	char concat[] = "TestString";
	MY_STRING hString1, hString2;

	hString1 = my_string_init_c_str("Test");
	hString2 = my_string_init_c_str("String");

	size = (hString1->get_size(hString1) + hString2->get_size(hString2));

	hString1->concat(hString1, hString2);

	if (*hString1->at(hString1, 0) == 'S')
	{
		status = FAILURE;
		printf("Concatenate function combines the two strings in the wrong order\n");
		strncpy(buffer, "test_concatenate_combines_two_strings_in_the_correct_order\n"
			"Concatenate function does not properly combine two strings", length);
	}
	else
	{
		for (i = 0; i < size && *hString1->at(hString1, i) == concat[i]; i++);

		if (i != size)
		{
			status = FAILURE;
			printf("Concatenate function mixed the characters in the strings\n");
			strncpy(buffer, "test_concatenate_combines_two_strings_in_the_correct_order\n"
				"Concatenate function does not properly combine two strings", length);
		}
		else
		{
			status = SUCCESS;
			strncpy(buffer, "test_concatenate_combines_two_strings_in_the_correct_order\n", length);
		}
	}

	hString1->destroy(&hString1);
	hString2->destroy(&hString2);
	return status;
}

Status test_c_str_changes_a_character_array_into_a_c_str(char* buffer, int length)
{
	Status status;
	char* string1;
	char string2[] = "Test1";
	int i, num_char = 5;

	MY_STRING hString;
	hString = my_string_init_c_str("Test1");

	string1 = hString->c_str(hString);

	for (i = 0; string1[i] == string2[i] && string2[i] != '\0'; i++);

	if (i != num_char)
	{
		status = FAILURE;
		printf("The c_str function did not properly convert the string given\n");
		strncpy(buffer, "test_c_str_changes_a_character_array_into_a_c_str\n"
			"\tThe c_str function failed to return a proper character pointer value\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_c_str_changes_a_character_array_into_a_c_str\n", length);
	}
	hString->destroy(&hString);
	return status;
}

Status test_c_str_returns_char_ptr_not_a_char_value(char* buffer, int length)
{
	Status status;
	char string1[] = "Test1";
	char* string2;

	MY_STRING hString;

	hString = my_string_init_c_str("Test1");

	string2 = hString->c_str(hString);

	if (*string1 != *string2)
	{
		status = FAILURE;
		printf("The c_str function did not return a char_ptr\n");
		strncpy(buffer, "test_c_str_return_char_ptr_not_a_char_value\n"
			"\tThe c_str function failed to return a proper character pointer value\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_c_str_return_char_ptr_not_a_char_value\n", length);
	}
	hString->destroy(&hString);
	return status;
}

//BRETT

Status test_init_default_capacity_greater_than_size(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	if (hString->get_capacity(hString) <= hString->get_size(hString))
	{

		strncpy(buffer, "test_init_default_capacity_greater_than_size "
			"my_string_init_default does not make capacity larger "
			"than size", length);
		hString->destroy(&hString);
		return FAILURE;
	}
	else
	{
		strncpy(buffer, "test_init_default_capacity_greater_than_size", length);
		hString->destroy(&hString);
		return SUCCESS;
	}

}

Status test_init_default_capacity_more_than0(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	if (hString->get_capacity(hString) < 1)
	{

		strncpy(buffer, "test_init_default_capacity_more_than0 "
			"my_string_init_default does not make capacity more "
			"than 0", length);
		hString->destroy(&hString);
		return FAILURE;
	}
	else
	{
		strncpy(buffer, "test_init_default_capacity_more_than0", length);
		hString->destroy(&hString);
		return SUCCESS;
	}

}


Status test_destroy_function(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	hString->destroy(&hString);
	if (hString != NULL)
	{

		strncpy(buffer, "test_destroy_function "
			"destroy does not free up hString", length);
		return FAILURE;
	}
	else
	{
		strncpy(buffer, "test_destroy_function "
			"works fine now bye bye.", length);
		return SUCCESS;
	}

}

Status test_push_function(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();

	if (hString->push_back(hString, 'c') == FAILURE)
	{

		strncpy(buffer, "test_push_function "
			"push_back does notadd item to hString", length);
		hString->destroy(&hString);
		return FAILURE;
	}
	else
	{
		strncpy(buffer, "test_push_function "
			"works fine now bye bye.", length);
		hString->destroy(&hString);
		return SUCCESS;
	}

}

Status test_push_size_resizing(char* buffer, int length)
{
	MY_STRING hString = NULL;
	int before, after;
	hString = my_string_init_default();
	before = hString->get_size(hString);
	hString->push_back(hString, 'c');
	after = hString->get_size(hString);

	if (before >= after)
	{

		strncpy(buffer, "test_push_size_resizing "
			"push_back does not resize hStrings size", length);
		hString->destroy(&hString);
		return FAILURE;
	}
	else
	{
		strncpy(buffer, "test_push_size_resizing "
			"works fine now bye bye.", length);
		hString->destroy(&hString);
		return SUCCESS;
	}

}

Status test_push_capacity_resizing(char* buffer, int length)
{
	MY_STRING hString = NULL;
	int before, after, i;
	hString = my_string_init_default();
	before = hString->get_capacity(hString);
	for (i = 0; i < 8; i++){
		hString->push_back(hString, 'c');
	}
	hString->push_back(hString, 'c');
	after = hString->get_capacity(hString);

	if (before >= after)
	{

		strncpy(buffer, "test_push_capacity_resizing "
			"push_back does not resize hStrings capacity", length);
		hString->destroy(&hString);
		return FAILURE;
	}
	else
	{
		strncpy(buffer, "test_push_capacity_resizing "
			"works fine now bye bye.", length);
		hString->destroy(&hString);
		return SUCCESS;
	}

}

Status test_init_c_str_takes_string(char* buffer, int length)
{
	MY_STRING hString;
	hString = my_string_init_c_str("this is my string.");
	if (hString == NULL)
	{
		strncpy(buffer, "test_init_c_str_takes_string "
			"init_c_str_takes_string does not take in a string", length);
		hString->destroy(&hString);
		return FAILURE;
	}
	else
	{
		strncpy(buffer, "test_init_c_str_takes_string "
			"works fine now bye bye.", length);
		hString->destroy(&hString);
		return SUCCESS;
	}
}

Status test_string_compare_equal(char* buffer, int length)
{
	MY_STRING hString1;
	MY_STRING hString2;
	hString1 = my_string_init_c_str("this is my string.");
	hString2 = my_string_init_c_str("this is my string.");
	if (hString1->string_compare(hString1, hString2) != 0)
	{
		strncpy(buffer, "test_string_compare_function "
			"string_compare_function does not fempute", length);
		hString1->destroy(&hString1);
		hString2->destroy(&hString2);
		return FAILURE;
	}
	else
	{
		strncpy(buffer, "test_string_compare_function "
			"ALL HAIL THE MIGHTY FEMPUTER!", length);
		hString1->destroy(&hString1);
		hString2->destroy(&hString2);
		return SUCCESS;
	}
}

Status test_string_compare_greater_than(char* buffer, int length)
{
	MY_STRING hString1;
	MY_STRING hString2;
	hString1 = my_string_init_c_str("this is a better string.");
	hString2 = my_string_init_c_str("this is my string.");
	if (hString1->string_compare(hString1, hString2) != -1)
	{
		strncpy(buffer, "test_string_compare_greater_than "
			"string_compare does not know how to human", length);
		hString1->destroy(&hString1);
		hString2->destroy(&hString2);
		return FAILURE;
	}
	else
	{
		strncpy(buffer, "test_string_compare_greater_than "
			"string_compare does infact know how to human", length);
		hString1->destroy(&hString1);
		hString2->destroy(&hString2);
		return SUCCESS;
	}
}

Status test_string_compare_less_than(char* buffer, int length)
{
	MY_STRING hString1;
	MY_STRING hString2;
	hString1 = my_string_init_c_str("this is my string.");
	hString2 = my_string_init_c_str("this is a better string.");
	if (hString1->string_compare(hString1, hString2) != 1)
	{
		strncpy(buffer, "test_string_compare_less_than "
			"string_compare put its baby in the road ", length);
		hString1->destroy(&hString1);
		hString2->destroy(&hString2);
		return FAILURE;
	}
	else
	{
		strncpy(buffer, "test_string_compare_function "
			"string_compare knew better than to put its baby in the road", length);
		hString1->destroy(&hString1);
		hString2->destroy(&hString2);
		return SUCCESS;
	}
}


Status test_at_function(char* buffer, int length)
{
	MY_STRING hString;
	hString = my_string_init_c_str("this is my string.");
	if (hString->at(hString, 1) == NULL)
	{
		strncpy(buffer, "test_at_function "
			"at_function doestn't work", length);
		hString->destroy(&hString);
		return FAILURE;
	}
	else
	{
		strncpy(buffer, "test_at_function "
			"works fine now bye bye.", length);
		hString->destroy(&hString);
		return SUCCESS;
	}
}

Status test_at_return_NULL(char* buffer, int length)
{
	MY_STRING hString;
	hString = my_string_init_c_str("this is my string.");
	if (hString->at(hString, -1) != NULL)
	{
		strncpy(buffer, "test_at_return_NULL "
			"at_function might not work", length);
		hString->destroy(&hString);
		return FAILURE;
	}
	else
	{
		strncpy(buffer, "test_at_return_NULL "
			"works fine now bye bye.", length);
		hString->destroy(&hString);
		return SUCCESS;
	}
}


Status test_init_get_size_function(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	if (hString->get_size(hString) != 0)
	{
		strncpy(buffer, "test_get_size_function "
			"get_size_function doestn't work", length);
		hString->destroy(&hString);
		return FAILURE;
	}
	else
	{
		strncpy(buffer, "test_get_size_function "
			"works fine now bye bye.", length);
		hString->destroy(&hString);
		return SUCCESS;
	}
}

Status test_pop_resizing(char* buffer, int length)
{
	MY_STRING hString = NULL;
	int before, after;
	hString = my_string_init_default();
	hString->push_back(hString, 'c');
	before = hString->get_size(hString);
	hString->pop_back(hString);
	after = hString->get_size(hString);

	if (before <= after)
	{

		strncpy(buffer, "test_pop_resizing "
			"pop_back does not resize hString", length);
		hString->destroy(&hString);
		return FAILURE;
	}
	else
	{
		strncpy(buffer, "test_pop_resizing "
			"works fine now bye bye.", length);
		hString->destroy(&hString);
		return SUCCESS;
	}

}

Status test_pop_return_fail(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	hString->pop_back(hString);
	if (hString->pop_back(hString) != FAILURE)
	{

		strncpy(buffer, "test_pop_return_fail "
			"pop_back does not work well.", length);
		hString->destroy(&hString);
		return FAILURE;
	}
	else
	{
		strncpy(buffer, "test_pop_return_fail "
			"works fine now bye bye.", length);
		hString->destroy(&hString);
		return SUCCESS;
	}

}

Status test_extraction_function(char* buffer, int length)
{
	MY_STRING hString = NULL;
	FILE* fptr;
	hString = my_string_init_default();
	
	fptr = fopen("extraction_test_LUNDY.txt", "w");
	fprintf(fptr, "Test");
	fclose(fptr);

	fptr = fopen("extraction_test_LUNDY.txt", "r");

	hString->extraction(hString, fptr);
	if (hString == NULL)
	{

		strncpy(buffer, "test_extraction_function "
			"extraction_function does not like you.", length);
		hString->destroy(&hString);
		return FAILURE;
	}
	else
	{
		strncpy(buffer, "test_extraction_function "
			"works fine now bye bye.", length);
		hString->destroy(&hString);
		return SUCCESS;
	}

}

Status test_concat_function(char* buffer, int length)
{
	MY_STRING hWord1;
	MY_STRING hWord2;
	hWord1 = my_string_init_c_str("Lets");
	hWord2 = my_string_init_c_str(" run");

	if (hWord1->concat(hWord1, hWord2) == FAILURE)
	{

		strncpy(buffer, "test_concat_function "
			"concat does not work.", length);
		hWord1->destroy(&hWord1);
		hWord2->destroy(&hWord2);

		return FAILURE;
	}
	else
	{
		strncpy(buffer, "test_concat_function "
			"works fine now bye bye.", length);
		hWord1->destroy(&hWord1);
		hWord2->destroy(&hWord2);
		return SUCCESS;
	}

}

Status test_concat_size_resize(char* buffer, int length)
{
	MY_STRING hWord1;
	MY_STRING hWord2;
	int before, after;
	hWord1 = my_string_init_c_str("Lets");
	hWord2 = my_string_init_c_str(" run");
	before = hWord1->get_size(hWord1);
	hWord1->concat(hWord1, hWord2);
	after = hWord1->get_size(hWord1);

	if (before >= after)
	{

		strncpy(buffer, "test_concat_size_resize "
			"concat does not resize hString1 size, p.s. that also might mean it "
			"did not concat the strings.", length);
		hWord1->destroy(&hWord1);
		hWord2->destroy(&hWord2);

		return FAILURE;
	}
	else
	{
		strncpy(buffer, "test_concat_size_resizing "
			"works fine now bye bye.", length);
		hWord1->destroy(&hWord1);
		hWord2->destroy(&hWord2);
		return SUCCESS;
	}

}

Status test_concat_capacity_resize(char* buffer, int length)
{
	MY_STRING hWord1;
	MY_STRING hWord2;
	int before, after;
	hWord1 = my_string_init_c_str("Lets");
	hWord2 = my_string_init_c_str(" run");
	before = hWord1->get_capacity(hWord1);
	hWord1->concat(hWord1, hWord2);
	after = hWord1->get_capacity(hWord1);

	if (before >= after)
	{

		strncpy(buffer, "test_concat_capacity_resize "
			"concat does not resize hString1 capacity, p.s. that also might mean it "
			"did not concat the strings.", length);
		hWord1->destroy(&hWord1);
		hWord2->destroy(&hWord2);

		return FAILURE;
	}
	else
	{
		strncpy(buffer, "test_concat_capacity_resizing "
			"works fine now bye bye.", length);
		hWord1->destroy(&hWord1);
		hWord2->destroy(&hWord2);
		return SUCCESS;
	}

}

Status test_c_str_function(char* buffer, int length)
{
	MY_STRING hString = NULL;
	int i;
	hString = my_string_init_default();
	
	i = hString->get_size(hString);
	hString->c_str(hString);
	if (hString->at(hString, i) != '\0')
	{

		strncpy(buffer, "test_c_str_function "
			"c_str function does not care about your problems.", length);
		hString->destroy(&hString);
		return FAILURE;
	}
	else
	{
		strncpy(buffer, "test_c_str_function "
			"works fine now bye bye.", length);
		hString->destroy(&hString);
		return SUCCESS;
	}

}

Status test_c_str_capacity_resize(char* buffer, int length)
{
	MY_STRING hString = NULL;
	int i;
	int j;
	hString = my_string_init_c_str("this is a string.");
	
	i = hString->get_capacity(hString);
	hString->push_back(hString, 'a');
	hString->c_str(hString);
	j = hString->get_capacity(hString);
	if (i >= j)
	{

		strncpy(buffer, "test_c_str_capacity_resize "
			"c_str function does not resize capacity.", length);
		hString->destroy(&hString);
		return FAILURE;
	}
	else
	{
		strncpy(buffer, "test_c_str_capacity_resize "
			"works fine now bye bye.", length);
		hString->destroy(&hString);
		return SUCCESS;
	}
}

//ANTHONY

Status AB_test_1_init(char* buffer, int length)
{
	MY_STRING thing;
	void* something;
	strncpy(buffer, "AB_test_1_init\n", length);
	thing = my_string_init_default();
	something = thing;
	thing->destroy(&thing);

	return (Status)(something != NULL);

}
Status AB_test_2_destroy(char* buffer, int length)
{
	MY_STRING thing;
	strncpy(buffer, "AB_test_2_destroy\n", length);

	thing = my_string_init_default();

	thing->destroy(&thing);
	return (Status)(thing == NULL);
}
Status AB_test_3_get_size(char* buffer, int length)
{
	MY_STRING thing;
	int size;
	strncpy(buffer, "AB_test_3_get_size\n", length);

	thing = my_string_init_default();
	size = thing->get_size(thing);
	thing->destroy(&thing);
	return  (Status)(size == 0);
}
Status AB_test_4_get_capacity(char* buffer, int length)
{
	MY_STRING thing;
	int capacity;
	strncpy(buffer, "AB_test_4_get_capacity\n", length);

	thing = my_string_init_default();
	capacity = thing->get_capacity(thing);
	thing->destroy(&thing);
	return (Status)(capacity == 8);
}
Status AB_test_5_pop_back_returns_status(char* buffer, int length)
{
	MY_STRING thing;
	Status something;
	strncpy(buffer, "AB_test_5_pop_back_returns_status\n", length);

	thing = my_string_init_default();
	something = thing->pop_back(thing);
	thing->destroy(&thing);
	return  (Status)(something == FAILURE);
}
Status AB_test_6_push_back_returns_status(char* buffer, int length)
{
	MY_STRING thing;
	Status something;
	strncpy(buffer, "AB_test_6_push_back_returns_status\n", length);

	thing = my_string_init_default();
	something = thing->push_back(thing, 'a');
	thing->destroy(&thing);
	return  (Status)(something);
}
Status AB_test_7_push_back_changes_size(char* buffer, int length)
{
	MY_STRING thing;
	int size;
	strncpy(buffer, "AB_test_7_push_back_changes_size\n", length);

	thing = my_string_init_default();
	thing->push_back(thing, 'a');
	size = thing->get_size(thing);
	thing->destroy(&thing);
	return  (Status)(size == 1);
}
Status AB_test_8_pop_back_changes_size(char* buffer, int length)
{
	MY_STRING thing;
	int size;
	strncpy(buffer, "AB_test_8_pop_back_changes_size\n", length);

	thing = my_string_init_default();
	thing->push_back(thing, 'a');
	thing->pop_back(thing);
	size = thing->get_size(thing);
	thing->destroy(&thing);
	return  (Status)(size == 0);
}
Status AB_test_10_at_returns_null_out_of_limits(char* buffer, int length)
{
	MY_STRING thing = my_string_init_default();
	strncpy(buffer, "AB_test_10_at_returns_null_out_of_limits\n", length);


	return (Status)(thing->at(thing, 0) == NULL);
}
Status AB_test_11_at_returns_address_of_char_in_index(char* buffer, int length)
{
	MY_STRING thing;
	char A;
	strncpy(buffer, "AB_test_11_at_returns_address_of_char_in_index\n", length);

	thing = my_string_init_default();

	thing->push_back(thing, 'A');
	A = *thing->at(thing, 0);
	thing->destroy(&thing);

	return  (Status)((A == 'A'));
}
Status AB_test_12_string_compare_same_returns_0(char* buffer, int length)
{
	MY_STRING thing;
	int a;
	strncpy(buffer, "AB_test_12_string_compare_same_returns_0\n", length);

	thing = my_string_init_default();

	thing->push_back(thing, 'A');
	a = thing->string_compare(thing, thing);
	thing->destroy(&thing);

	return  (Status)(a == 0);
}
Status AB_test_13_string_compare_returns_negative_if_first_comes_before(char* buffer, int length)
{
	MY_STRING thing1, thing2;
	int a;
	strncpy(buffer, "AB_test_13_string_compare_returns_negative_if_first_comes_before\n", length);

	thing1 = my_string_init_default();
	thing2 = my_string_init_default();
	thing1->push_back(thing1, 'A');
	thing2->push_back(thing2, 'B');
	a = thing1->string_compare(thing1, thing2);
	thing1->destroy(&thing1);
	thing2->destroy(&thing2);
	return  (Status)(a < 0);
}
Status AB_test_14_string_compare_returns_positive_if_first_comes_after(char* buffer, int length)
{
	MY_STRING thing1, thing2;
	int a;
	strncpy(buffer, "AB_test_14_string_compare_returns_positive_if_first_comes_after\n", length);

	thing1 = my_string_init_default();
	thing2 = my_string_init_default();
	thing1->push_back(thing1, 'A');
	thing2->push_back(thing2, 'B');
	a = thing1->string_compare(thing2, thing1);
	thing1->destroy(&thing1);
	thing2->destroy(&thing2);
	return  (Status)(a > 0);
}
Status AB_test_15_init_c_string(char* buffer, int length)
{
	MY_STRING thing1, thing2;
	char word[10] = "HELLO";
	int a;
	strncpy(buffer, "AB_test_15_init_c_string\n", length);

	thing1 = my_string_init_default();
	thing2 = my_string_init_c_str(word);
	thing1->push_back(thing1, 'H');
	thing1->push_back(thing1, 'E');
	thing1->push_back(thing1, 'L');
	thing1->push_back(thing1, 'L');
	thing1->push_back(thing1, 'O');
	a = thing1->string_compare(thing1, thing2);
	thing1->destroy(&thing1);
	thing2->destroy(&thing2);
	return  (Status)(a == 0);
}
Status AB_test_16_concat(char* buffer, int length)
{
	MY_STRING thing1, thing2;
	int a;
	char word1[10] = "HELLO", word2[10] = "GOODBYE";
	char word12[20] = "HELLOGOODBYE";
	strncpy(buffer, "AB_test_16_concat\n", length);

	thing1 = my_string_init_c_str(word1);
	thing2 = my_string_init_c_str(word2);
	thing1->concat(thing1, thing2);
	thing2->destroy(&thing2);
	thing2 = my_string_init_c_str(word12);
	a = thing1->string_compare(thing1, thing2);
	thing1->destroy(&thing1);
	thing2->destroy(&thing2);
	return  (Status)(a == 0);
}
Status AB_test_17_extraction_on_empty_fails(char* buffer, int length)
{
	FILE* fp;
	MY_STRING thing;
	Status something;
	strncpy(buffer, "AB_test_17_extraction_on_empty_fails\n", length);

	thing = my_string_init_default();
	fp = fopen("blank.txt", "w");
	fclose(fp);
	fp = fopen("blank.txt", "r");
	if (fp == NULL)
	{
		exit(1);
	}

	something = thing->extraction(thing, fp);
	fclose(fp);
	thing->destroy(&thing);
	return 	(Status)(something == FAILURE);
}

Status AB_test_18_extraction_on_white_spaces_contains_NULL(char* buffer, int length)
{
	FILE* fp;
	MY_STRING thing;
	char* something;
	strncpy(buffer, "AB_test_18_extraction_on_white_spaces_contains_NULL\n", length);

	thing = my_string_init_default();
	fp = fopen("blank.txt", "w");
	if (fp == NULL)
	{
		exit(1);
	}
	fprintf(fp, "   \t   \n");
	fclose(fp);
	fp = fopen("blank.txt", "r");
	if (fp == NULL)
	{
		exit(1);
	}
	thing->extraction(thing, fp);
	fclose(fp);

	something = thing->c_str(thing);
	thing->destroy(&thing);
	return 	(Status)(something == NULL);
}
Status AB_test_19_extraction_gets_one_word_from_file(char* buffer, int length)
{
	FILE* fp;
	MY_STRING thing1, thing2;
	int a;
	strncpy(buffer, "AB_test_19_extraction_gets_one_word_from_file\n", length);

	thing1 = my_string_init_default();
	fp = fopen("Big apples.txt", "w");
	if (fp == NULL)
	{
		exit(1);
	}
	fprintf(fp, "Big apples\t\n\n      third");
	fclose(fp);
	fp = fopen("Big apples.txt", "r");
	if (fp == NULL)
	{
		exit(1);
	}
	thing1->extraction(thing1, fp);
	fclose(fp);
	thing2 = my_string_init_c_str("Big");

	a = thing1->string_compare(thing1, thing2);
	thing1->destroy(&thing1);
	thing2->destroy(&thing2);
	return 	(Status)(a == 0);
}
Status AB_test_20_string_at_capacity_resizes_for_c_str_but_does_not_change_size(char* buffer, int length)
{
	MY_STRING thing;
	int i, max, size, capacity;
	strncpy(buffer, "AB_test_20_string_at_capacity_resizes_for_c_str_but_does_not_change_size\n", length);

	thing = my_string_init_default();
	max = thing->get_capacity(thing);
	for (i = 0; i < max; i++)
	{
		thing->push_back(thing, 'A');
	}
	thing->c_str(thing);
	size = thing->get_size(thing);
	capacity = thing->get_capacity(thing);
	thing->destroy(&thing);
	return (Status)(size == max && capacity > max);
}
Status AB_test_21_extraction_can_skip_white_space(char* buffer, int length)
{
	FILE* fp;
	MY_STRING thing1, thing2;
	int a;
	strncpy(buffer, "AB_test_21_extraction_can_skip_white_space\n", length);

	thing1 = my_string_init_default();
	fp = fopen("Big apples.txt", "r");
	if (fp == NULL)
	{
		exit(1);
	}
	for (a = 0; a < 3; a++)
	{
		thing1->extraction(thing1, fp);
	}
	fclose(fp);
	thing2 = my_string_init_c_str("third");

	a = thing1->string_compare(thing1, thing2);
	thing1->destroy(&thing1);
	thing2->destroy(&thing2);
	return 	(Status)(a == 0);
}
Status AB_test_22_destroying_a_non_exisiting_handle_does_not_crash_program(char* buffer, int length)
{
	MY_STRING something;
	FILE* nothing;
	strncpy(buffer, "AB_test_22_destroying_a_non_exisiting_handle_does_not_crash_program\n", length);

	nothing = NULL;
	something = my_string_init_default();
	something->destroy(&something);
	return (Status)(nothing == NULL&&something == NULL);

}
Status AB_test_23_string_ing_strings(char* buffer, int length)
{
	MY_STRING thing1, thing2, thing3;
	char word[10] = "goodbye";
	int a, b;
	strncpy(buffer, "AB_test_23_string_ing_strings\n", length);

	thing1 = my_string_init_default();
	thing1->push_back(thing1, '1');
	thing2 = my_string_init_c_str(word);
	thing2->push_back(thing2, '2');
	thing3 = my_string_init_c_str(thing2->c_str(thing2));
	thing3->push_back(thing3, '3');
	thing1->concat(thing1, thing2);
	thing1->concat(thing1, thing3);
	thing2->destroy(&thing2);
	thing3->destroy(&thing3);
	thing2 = my_string_init_c_str(thing1->c_str(thing1));
	thing3 = my_string_init_c_str(thing2->c_str(thing2));
	a = thing3->string_compare(thing3, thing1);
	b = thing1->string_compare(thing2, thing1);

	thing1->destroy(&thing1);
	thing2->destroy(&thing2);
	thing3->destroy(&thing3);

	return (Status)(a == 0 && b == 0);
}
Status AB_test_24_init_empty_str_force_pop_off_of_nothing(char* buffer, int length)
{
	MY_STRING thing;
	int i;
	strncpy(buffer, "AB_test_24_init_empty_str_force_pop_off_of_nothing\n", length);

	thing = my_string_init_c_str("");

	for (i = 0; i < 5; i++)
	{
		if (thing->c_str(thing) != NULL)
		{
			return FAILURE;
		}
		if (FAILURE != thing->pop_back(thing))
		{
			return FAILURE;
		}
	}
	thing->destroy(&thing);
	return (Status)(thing == NULL);
}
Status AB_test_25_read_through_large_doc_successfully_stopping_at_end(char* buffer, int length)
{
	MY_STRING thing;
	FILE* fp;
	int i;
	strncpy(buffer, "AB_test_25_read_through_large_doc_successfully_stopping_at_end\n", length);

	fp = fopen("lot_o_words.txt", "w");
	if (fp == NULL)
	{
		printf("error openning a testing file\n");
		exit(1);
	}
	for (i = 0; i < 500; i++)
	{
		fprintf(fp, "The quick brown fox jumped over the lazy dogs.\n");
	}
	fclose(fp);
	thing = my_string_init_default();
	fp = fopen("lot_o_words.txt", "r");
	if (fp == NULL)
	{
		printf("error making testing doc.\n");
		exit(1);
	}

	while (thing->extraction(thing, fp));

	thing->destroy(&thing);

	return (Status)(thing == NULL);
}
Status AB_test_26_compare_strings_does_not_account_for_less_length(char* buffer, int length)
{
	MY_STRING thing1, thing2;
	int a;
	strncpy(buffer, "AB_test_26_compare_strings_does_not_account_for_less_length\n", length);

	thing1 = my_string_init_c_str("ab");
	thing2 = my_string_init_c_str("abc");
	a = thing1->string_compare(thing1, thing2);
	thing1->destroy(&thing1);
	thing2->destroy(&thing2);
	return (Status)(a < 0);
}
Status AB_test_27_compare_strings_does_not_account_for_more_length(char* buffer, int length)
{
	MY_STRING thing1, thing2;
	int a;
	strncpy(buffer, "AB_test_27_compare_strings_does_not_account_for_more_length\n", length);

	thing1 = my_string_init_c_str("abc");
	thing2 = my_string_init_c_str("ab");
	a = thing1->string_compare(thing1, thing2);
	thing1->destroy(&thing1);
	thing2->destroy(&thing2);
	return (Status)(a > 0);
}
Status AB_test_28_compare_strings_does_not_account_for_capitol_letters(char* buffer, int length)
{
	MY_STRING thing1, thing2;
	int a;
	strncpy(buffer, "AB_test_28_compare_strings_does_not_account_for_capitol_letters\n", length);

	thing1 = my_string_init_c_str("AB");
	thing2 = my_string_init_c_str("ab");
	a = thing1->string_compare(thing1, thing2);
	thing1->destroy(&thing1);
	thing2->destroy(&thing2);
	return (Status)(a < 0);
}





