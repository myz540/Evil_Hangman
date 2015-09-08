/*

This file contains the implementation of the AVL tree used to store the bins 
which will be used to in the Evil_Hangman game, associated with AVL_tree.h header

*/

#include "AVL_tree.h"

//Returns height of tree
int height(Node_ptr N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

//Returns max of two ints
int maximum(int a, int b)
{
	return (a > b) ? a : b;
}

//Get New Node and returns pointer to the node
Node_ptr newNode(MY_STRING key, MY_STRING temp_word)
{
	Node_ptr temp = (Node_ptr)malloc(sizeof(Node));
	temp->string_key = my_string_init_default();
	temp->string_key->string_assignment(&temp->string_key, key);
	temp->string_bin = my_vector_init_default(temp->string_key->destroy, temp->string_key->string_assignment);
	temp->string_bin->push_back(temp->string_bin, temp_word);

	temp->left = NULL;
	temp->right = NULL;
	temp->height = 1;  // new node is initially added at leaf
	return temp;
}

//Right rotate subtree rooted with y
Node_ptr rightRotate(Node_ptr y)
{
	Node_ptr x = y->left;
	Node_ptr T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = maximum(height(y->left), height(y->right)) + 1;
	x->height = maximum(height(x->left), height(x->right)) + 1;

	// Return new root
	return x;
}

//Left rotate subtree rooted with x
Node_ptr leftRotate(Node_ptr x)
{
	Node_ptr y = x->right;
	Node_ptr T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	//  Update heights
	x->height = maximum(height(x->left), height(x->right)) + 1;
	y->height = maximum(height(y->left), height(y->right)) + 1;

	// Return new root
	return y;
}

//Returns Balance factor of node N (height of left subtree - height of right subtree)
int getBalance(Node_ptr N)
{
	if (N == NULL){
		return 0;
	}

	return height(N->left) - height(N->right);
}

Node_ptr insert(Node_ptr node, MY_STRING key, MY_STRING temp_word)
{
	Node_ptr temp;

	//Insert into BST as usual
	if (node == NULL){
		return(newNode(key, temp_word));
	}

	if (key->string_compare(key, node->string_key) == -1){
		node->left = insert(node->left, key, temp_word);
	}
	else{
		node->right = insert(node->right, key, temp_word);
	}

	//Update height
	node->height = maximum(height(node->left), height(node->right)) + 1;

	//Get balance factor
	int balance = getBalance(node);

	//4 cases of unbalanced tree

	//LL
	temp = node->left;
	if (balance > 1 && key->string_compare(key, temp->string_key) == -1){
		return rightRotate(node);
	}

	//RR
	temp = node->right;
	if (balance < -1 && key->string_compare(key, temp->string_key) == 1){
		return leftRotate(node);
	}

	//LR
	temp = node->left;
	if (balance > 1 && key->string_compare(key, temp->string_key) == 1)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	//RL
	temp = node->right;
	if (balance < -1 && key->string_compare(key, temp->string_key) == -1)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	/* return the (unchanged) node pointer */
	return node;
}

//Pre-order print of tree
void print_tree(Node_ptr root)
{
	if (root != NULL)
	{
		printf("%s\t%d\n", root->string_key->c_str(root->string_key), root->string_bin->get_size(root->string_bin));
		print_tree(root->left);
		print_tree(root->right);
	}
}

//Returns key given a character guess and a MY_STRING object
MY_STRING generate_key(MY_STRING hWord, char c, MY_STRING temp_key)
{
	int i;

	while (temp_key->get_size(temp_key) != 0){
		temp_key->pop_back(temp_key);
	}

	for (i = 0; i < hWord->get_size(hWord); i++){
		if (c == *hWord->at(hWord, i)){
			temp_key->push_back(temp_key, c);
		}
		else{
			temp_key->push_back(temp_key, '-');
		}
	}

	return temp_key;
}

//Search of tree for a given key, returns pointer to that node
Node_ptr search(Node_ptr root, MY_STRING key)
{
	if (root == NULL){
		return NULL;
	}

	if (root->string_key->string_compare(key, root->string_key) == -1){
		return search(root->left, key);
	}
	if (root->string_key->string_compare(key, root->string_key) == 1) {
		return search(root->right, key);
	}
	else {
		return root;
	}
}

//Postorder search of tree for the largest bin, stores max node in max_node
void find_largest_bin(Node_ptr root, Node_ptr* max_node, int* max_size)
{
	if (root == NULL){
		return;
	}

	find_largest_bin(root->left, max_node, max_size);
	find_largest_bin(root->right, max_node, max_size);

	if (root->string_bin->get_size(root->string_bin) > *max_size){
		*max_node = root;
		*max_size = root->string_bin->get_size(root->string_bin);
	}
}

void destroy_tree(Node_ptr root)
{
	if (root != NULL)
	{
		destroy_tree(root->left);
		destroy_tree(root->right);
		root->string_key->destroy(root->string_key);
		root->string_bin->destroy(root->string_bin);
		free(root);
	}
}
