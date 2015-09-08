/*

String manipulation module for C

*/

#include <ctype.h>
#include "my_string.h"

void my_string_destroy(Item_ptr* phMy_string);
Status my_string_pushback(MY_STRING hMy_string, char letter);
Status my_string_popback(MY_STRING hMy_string);
int my_string_get_size(MY_STRING hMy_string);            //accessor
int my_string_get_capacity(MY_STRING hMy_string);        //accessor
char* my_string_at(MY_STRING, int);
Status my_string_extraction(MY_STRING hMy_string, FILE* fptr);
char* my_c_string(MY_STRING hMy_string);
int my_string_compare(MY_STRING hMy_string1, MY_STRING hMy_string2);
Status my_string_concatenate(MY_STRING destination, MY_STRING add);
Status get_line(MY_STRING hMy_string, FILE* fp);
Status string_assignment(Item_ptr* pLeft, Item_ptr pRight);

typedef struct my_string{
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
	Status(*get_line)(MY_STRING, FILE*);
	Status(*string_assignment)(Item_ptr*, Item_ptr);

	/******PRIVATE******/
	char* data;
	int size;
	int capacity;
} My_string;

MY_STRING my_string_init_default(void)
{
	My_string* pMy_string = (My_string*)malloc(sizeof(My_string));
	if (pMy_string == NULL){
		printf("Failed to allocate space\n");
		return NULL;
	}

	pMy_string->size = 0;
	pMy_string->capacity = 8;
	pMy_string->data = (char*)malloc(sizeof(char) * pMy_string->capacity);
	if (pMy_string->data == NULL){
		printf("Failed to allocate space for data elements\n");
		free(pMy_string);
		return NULL;
	}

	pMy_string->destroy = my_string_destroy;
	pMy_string->push_back = my_string_pushback;
	pMy_string->pop_back = my_string_popback;
	pMy_string->get_size = my_string_get_size;
	pMy_string->get_capacity = my_string_get_capacity;
	pMy_string->at = my_string_at;
	pMy_string->string_compare = my_string_compare;
	pMy_string->extraction = my_string_extraction;
	pMy_string->c_str = my_c_string;
	pMy_string->concat = my_string_concatenate;
	pMy_string->get_line = get_line;
	pMy_string->string_assignment = string_assignment;

	return (MY_STRING)pMy_string;
}

MY_STRING my_string_init_c_str(const char* string)
{
	int i = 0;
	My_string* pMy_string = (My_string*)malloc(sizeof(My_string));
	if (pMy_string == NULL){
		printf("Failed to allocate space\n");
		return NULL;
	}

	while (string[i] != '\0'){
		i++;
	}

	pMy_string->size = i;
	pMy_string->capacity = i + 1;
	pMy_string->data = (char*)malloc(sizeof(char) * pMy_string->capacity);
	if (pMy_string->data == NULL){
		printf("Failed to allocate space for data elements\n");
		free(pMy_string);
		return NULL;
	}

	for (i = 0; i < pMy_string->size; i++){
		pMy_string->data[i] = string[i];
	}

	pMy_string->destroy = my_string_destroy;
	pMy_string->push_back = my_string_pushback;
	pMy_string->pop_back = my_string_popback;
	pMy_string->get_size = my_string_get_size;
	pMy_string->get_capacity = my_string_get_capacity;
	pMy_string->at = my_string_at;
	pMy_string->string_compare = my_string_compare;
	pMy_string->extraction = my_string_extraction;
	pMy_string->c_str = my_c_string;
	pMy_string->concat = my_string_concatenate;
	pMy_string->get_line = get_line;
	pMy_string->string_assignment = string_assignment;

	return (MY_STRING)pMy_string;
}

void my_string_destroy(Item_ptr* phItem)
{
	My_string* temp = (My_string*)*phItem;

	if (temp != NULL){
		free(temp->data);
		free(temp);
		*phItem = NULL;
	}

	return;
}

Status my_string_pushback(MY_STRING hMy_string, char letter)
{
	My_string* pMy_string = (My_string*)hMy_string;
	int i;

	if (pMy_string->size >= pMy_string->capacity){
		char* temp = (char*)malloc(sizeof(char) * pMy_string->capacity * 2);
		if (temp == NULL){
			printf("Failed to allocate space for larger string\n");
			return FAILURE;
		}

		for (i = 0; i < pMy_string->size; i++){
			temp[i] = pMy_string->data[i];
		}

		pMy_string->capacity *= 2;
		free(pMy_string->data);
		pMy_string->data = temp;
	}

	pMy_string->data[pMy_string->size] = letter;
	pMy_string->size++;

	return SUCCESS;
}

Status my_string_popback(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*)hMy_string;

	if (pMy_string->size <= 0){
		return FAILURE;
	}

	pMy_string->size--;

	return SUCCESS;
}

int my_string_get_size(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*)hMy_string;

	return pMy_string->size;
}

int my_string_get_capacity(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*)hMy_string;
	return pMy_string->capacity;
}

char* my_string_at(MY_STRING hMy_string, int index)
{
	My_string* pMy_string = (My_string*)hMy_string;

	if (index < 0 || index >= pMy_string->size){
		return NULL;
	}

	return &pMy_string->data[index];
}

int my_string_compare(MY_STRING hMy_string1, MY_STRING hMy_string2)
{
	int i = 0;
	int size;

	if (hMy_string1->get_size(hMy_string1) < hMy_string2->get_size(hMy_string2)){
		size = hMy_string1->get_size(hMy_string1);
	}
	else {
		size = hMy_string2->get_size(hMy_string2);
	}

	for (i = 0; i < size; i++){
		if (*hMy_string1->at(hMy_string1, i) < *hMy_string2->at(hMy_string2, i)){
			return -1;
		}
		else if (*hMy_string1->at(hMy_string1, i) > *hMy_string2->at(hMy_string2, i)){
			return 1;
		}
	}
	if (hMy_string1->get_size(hMy_string1) < hMy_string2->get_size(hMy_string2)){
		return -1;
	}
	else if (hMy_string1->get_size(hMy_string1) > hMy_string2->get_size(hMy_string2)){
		return 1;
	}
	else{
		return 0;
	}
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fptr)
{
	My_string* pMy_string = (My_string*)hMy_string;
	char c;
	int conversions;

	if (fptr == NULL){
		printf("Invalid file pointer\n");
		return FAILURE;
	}

	pMy_string->size = 0;

	conversions = fscanf(fptr, " %c", &c);
	if (conversions == EOF){
		return FAILURE;
	}
	while (!isspace(c) && isalpha(c) && conversions != EOF){
		pMy_string->push_back((MY_STRING)pMy_string, c);
		conversions = fscanf(fptr, "%c", &c);
	}

	return SUCCESS;
}

char* my_c_string(MY_STRING hMy_string)
{
	int i;
	My_string* pMy_string = (My_string*)hMy_string;

	if (pMy_string->size == 0){
		return NULL;
	}

	if (pMy_string->size >= pMy_string->capacity){
		char* temp = (char*)malloc(sizeof(char) * pMy_string->capacity * 2);
		if (temp == NULL){
			printf("Failed to allocate space for larger string\n");
			return NULL;
		}

		for (i = 0; i < pMy_string->size; i++){
			temp[i] = pMy_string->data[i];
		}

		pMy_string->capacity *= 2;
		free(pMy_string->data);
		pMy_string->data = temp;
	}

	pMy_string->data[pMy_string->size] = '\0';

	return pMy_string->data;
}

Status my_string_concatenate(MY_STRING destination, MY_STRING add)
{
	int i;
	if (destination == NULL || add == NULL){
		return FAILURE;
	}

	for (i = 0; i < add->get_size(add); i++){
		destination->push_back(destination, *add->at(add, i));
	}

	return SUCCESS;
}

Status get_line(MY_STRING hMy_string, FILE* fp)
{
	My_string* pMy_string = (My_string*)hMy_string;
	int conversions = 0;
	char c;

	if (fp == NULL){
		printf("Invalid file pointer\n");
		return FAILURE;
	}

	pMy_string->size = 0;

	conversions = fscanf(fp, "%c", &c);
	if (conversions == EOF){
		return FAILURE;
	}

	while (c != '\n' && conversions != EOF){
		hMy_string->push_back(hMy_string, c);
		conversions = fscanf(fp, "%c", &c);
	}

	return SUCCESS;
}


Status string_assignment(Item_ptr* left, Item_ptr right)
{
	MY_STRING pLeft = (MY_STRING)*left;
	MY_STRING pRight = (MY_STRING)right;
	int i;

	if (pLeft == NULL){
		pLeft = my_string_init_default();
		if (pLeft == NULL){
			return FAILURE;
		}
	}

	while (pLeft->get_size(pLeft) != 0){
		pLeft->pop_back(pLeft);
	}

	for (i = 0; i < pRight->get_size(pRight); i++){
		pLeft->push_back(pLeft, *pRight->at(pRight, i));
	}

	*left = pLeft;

	return SUCCESS;
}


