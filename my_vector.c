/*

Vector object module implementation

*/

#include "my_vector.h"

//Precondition: hMy_vector holds the address of an opaque object of type MY_VECTOR ready to be destroyed.
//Postcondition: All memory for the vector indicated by hMy_vector has been released.
void my_vector_destroy(MY_VECTOR* phMy_vector);
Status my_vector_push_back(MY_VECTOR hMy_vector, Item_ptr item);
Status my_vector_pop_back(MY_VECTOR hMy_vector);
Item_ptr my_vector_at(MY_VECTOR hMy_vector, int index);
int my_vector_get_size(MY_VECTOR hMy_vector); //Accessor function
int my_vector_get_capacity(MY_VECTOR hMy_vector); //Accessor function

struct my_vector
{
	/*****PUBLIC********/
	void(*destroy)(MY_VECTOR* phMy_vector);
	Status(*push_back)(MY_VECTOR hMy_vector, Item_ptr item);
	Status(*pop_back)(MY_VECTOR hMy_vector);
	Item_ptr(*at)(MY_VECTOR hMy_vector, int index);
	int(*get_size)(MY_VECTOR hMy_vector);
	int(*get_capacity)(MY_VECTOR hMy_vector);


	/*****PRIVATE*******/
	int size;
	int capacity;
	Item_ptr* data;
	//Precondition:
	//Postcondition: item_handle is set to NULL and item is destroy properly
	void(*item_destroy)(Item_ptr* item_handle);
	//Precondition:
	//Postcondition:if item_handle is not NULL then we try to use the space
	//already allocated to item referred to by item_handle for a copy of item.  If 
	//assign fails then item_handle will be NULL, otherwise item_handle will be 
	//the address of an item that has a complete and independent copy of item.
	Status(*item_assign)(Item_ptr* item_handle, Item_ptr item);
	//function pointer to a function that can assign (deep copy) a data item.
};

typedef struct my_vector My_vector;
typedef My_vector* My_vector_ptr;

MY_VECTOR my_vector_init_default(void(*item_destroy)(Item_ptr* item_handle),
	Status(*item_assign)(Item_ptr* item_handle, Item_ptr item))  //ITEM
{
	My_vector_ptr pVector = (My_vector_ptr)malloc(sizeof(My_vector));
	int i;
	if (pVector != NULL)
	{
		pVector->size = 0;
		pVector->capacity = 1;
		pVector->data = (Item_ptr*)malloc(sizeof(Item_ptr) * pVector->capacity);
		pVector->destroy = my_vector_destroy;
		pVector->push_back = my_vector_push_back;
		pVector->get_size = my_vector_get_size;
		pVector->get_capacity = my_vector_get_capacity;
		pVector->pop_back = my_vector_pop_back;
		pVector->at = my_vector_at;
		pVector->item_destroy = item_destroy;
		pVector->item_assign = item_assign;
		if (pVector->data != NULL)
		{
			for (i = 0; i<pVector->capacity; i++)
			{
				pVector->data[i] = NULL;
			}
		}
		else
		{
			free(pVector);
			pVector = NULL;
		}
	}
	return (MY_VECTOR)pVector;
}

void my_vector_destroy(MY_VECTOR* phMy_vector)
{
	My_vector_ptr temp = (My_vector_ptr)*phMy_vector;
	int i;

	if (temp != NULL)
	{
		for (i = 0; i<temp->capacity; i++)
		{
			if (temp->data[i] != NULL)
			{
				temp->item_destroy(&temp->data[i]);
			}
		}
		free(temp->data);
		free(temp);
		*phMy_vector = NULL;
	}
}

Status my_vector_push_back(MY_VECTOR hMy_vector, Item_ptr item)
{
	My_vector_ptr pVector = (My_vector_ptr)hMy_vector;
	int i;
	Status status;

	if (pVector->size >= pVector->capacity)
	{
		Item_ptr *temp;
		pVector->capacity *= 2;
		temp = (Item_ptr*)malloc(sizeof(Item_ptr) * pVector->capacity);
		if (temp == NULL)
		{
			pVector->capacity /= 2;
			return FAILURE;
		}
		for (i = 0; i<pVector->capacity; i++)
		{
			temp[i] = NULL;
		}
		for (i = 0; i<pVector->size; i++)
		{
			temp[i] = pVector->data[i]; //shallow copy
		}
		free(pVector->data);
		pVector->data = temp;
	}

	status = pVector->item_assign(&pVector->data[pVector->size], item);  //Deep copy
	if (status == FAILURE)
	{
		return FAILURE;
	}
	pVector->size++;

	return SUCCESS;
}

int my_vector_get_size(MY_VECTOR hMy_vector)
{
	My_vector_ptr pVector = (My_vector_ptr)hMy_vector;

	return pVector->size;
}

int my_vector_get_capacity(MY_VECTOR hMy_vector)
{
	My_vector_ptr pVector = (My_vector_ptr)hMy_vector;

	return pVector->capacity;
}

Status my_vector_pop_back(MY_VECTOR hMy_vector)
{
	My_vector_ptr pVector = (My_vector_ptr)hMy_vector;

	if (pVector->size <= 0)
	{
		return FAILURE;
	}
	else
	{
		pVector->size--;
	}
	return SUCCESS;
}

Item_ptr my_vector_at(MY_VECTOR hMy_vector, int index)
{
	My_vector_ptr pVector = (My_vector_ptr)hMy_vector;

	if (index < 0 || index > pVector->size - 1) //array bounds check
	{
		return NULL;
	}
	else
	{
		return (pVector->data[index]);
	}
}
