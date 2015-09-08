/*

This file contains the header associated with the AVL_tree.c implementation file

*/

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include "status.h"
#include "my_string.h"
#include "my_vector.h"

struct node;
typedef struct node Node;
typedef Node* Node_ptr;

struct node
{
	MY_STRING string_key;
	MY_VECTOR string_bin;
	Node_ptr *left;
	Node_ptr *right;
	int height;
};

int height(Node_ptr N);
int maximum(int a, int b);
Node_ptr newNode(MY_STRING key, MY_STRING temp_word);
Node_ptr rightRotate(Node_ptr y);
Node_ptr leftRotate(Node_ptr x);
int getBalance(Node_ptr N);
Node_ptr insert(Node_ptr node, MY_STRING key, MY_STRING temp_word);
void print_tree(Node_ptr root);
MY_STRING generate_key(MY_STRING hWord, char c, MY_STRING temp_key);
Node_ptr search(Node_ptr root, MY_STRING key);
void find_largest_bin(Node_ptr root, Node_ptr* max_node, int* max_size);

#endif
