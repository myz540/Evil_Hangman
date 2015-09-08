/*

String manipulation module header

*/

#ifndef MY_STRING_H
#define MY_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include "status.h"

typedef void* Item_ptr;
struct my_string_public;
typedef struct my_string_public* MY_STRING;

struct my_string_public{
	/******PUBLIC******/
	void(*destroy)(Item_ptr*);
	Status(*push_back)(MY_STRING, char);
	Status(*pop_back)(MY_STRING);
	int(*get_size)(MY_STRING);             //accessor
	int(*get_capacity)(MY_STRING);         //accessor
	char* (*at)(MY_STRING, int);
	Status(*extraction)(MY_STRING, FILE*);
	char* (*c_str)(MY_STRING);
	int(*string_compare)(MY_STRING, MY_STRING);
	Status(*concat)(MY_STRING, MY_STRING);
	Status(*get_line)(MY_STRING hMy_string, FILE* fp);
	Status(*string_assignment)(Item_ptr*, Item_ptr);
};


//Precondition: NONE
//Postcondition: Returns a MY_STRING object that can hold 8 characters
MY_STRING my_string_init_default(void);

//Precondition: Provide function with const char*
//Postcondition: Returns a MY_STRING object with size equal to the
//	size of the string read, and a capacity of one greater in case the user
//	wants to append a null terminator character to make a c-string
MY_STRING my_string_init_c_str(const char*);

#endif

