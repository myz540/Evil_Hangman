/*

Vector object header file

*/

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <stdlib.h>
#include <stdio.h>
#include "status.h"

struct my_vector_public;
typedef struct my_vector_public* MY_VECTOR;

struct my_vector_public
{
	/*****PUBLIC********/
	//Precondition: hMy_vector holds the address of an opaque
	//              object of type MY_VECTOR ready to be destroyed.
	//Postcondition: All memory for the vector indicated by hMy_vector
	//               has been released.
	void(*destroy)(MY_VECTOR* phMy_vector);
	Status(*push_back)(MY_VECTOR hMy_vector, Item_ptr item);
	Status(*pop_back)(MY_VECTOR hMy_vector);
	Item_ptr(*at)(MY_VECTOR hMy_vector, int index); //checks array bounds
	int(*get_size)(MY_VECTOR hMy_vector); //Accessor function
	int(*get_capacity)(MY_VECTOR hMy_vector); //Accessor function
};


//Precondition: NONE
//Postcondition: An opaque object for MY_VECTOR has been created that can hold 1 item and
//               currently holds none.
//Precondition:
//Postcondition: item_handle is set to NULL and item is destroy properly
//void (*item_destroy)(Item_ptr* item_handle);
//Precondition:
//Postcondition:if item_handle is not NULL then we try to use the space
//already allocated to item referred to by item_handle for a copy of item.  If 
//assign fails then item_handle will be NULL, otherwise item_handle will be 
//the address of an item that has a complete and independent copy of item.
//Status (*item_assign)(Item_ptr* item_handle, Item_ptr item);
MY_VECTOR my_vector_init_default(void(*item_destroy)(Item_ptr* item_handle), Status (*item_assign)(Item_ptr* item_handle, Item_ptr item));

#endif
