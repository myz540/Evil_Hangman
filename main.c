/*
 
	Evil Hangman final project
	91.102
	Mike Zhong and Brett Lundy

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_vector.h"
#include "my_string.h"
#include "AVL_tree.h"

void clear_keyboard_buffer(void);
void play_hangman(MY_VECTOR* word_size);
void process_guess(MY_VECTOR* word_bin, Node_ptr* pHead, MY_STRING* current_key, MY_STRING* letters_geussed);
int continue_play(void);

int main(int argc, char* argv[])
{
	MY_VECTOR word_size[50];
	MY_STRING hWord;
	int i;
	FILE* f_ptr;

	//INIT SPACE FOR VECTOR OF MY_VECTORS WHERE INDEX OF VECTOR IS SIZE OF WORD
	//AND A MY_STRING VARIABLE TO EXTRACT THE WORDS FROM THE DICTIONARY TEXT FILE
	hWord = my_string_init_default();
	for (i = 0; i < 50; i++){
		word_size[i] = my_vector_init_default(hWord->destroy, hWord->string_assignment);
	}

	f_ptr = fopen("dictionary.txt", "r");
	if (f_ptr == NULL){
		printf("failed to open file\n");
	}

	while (hWord->extraction(hWord, f_ptr) == SUCCESS){
		word_size[hWord->get_size(hWord)]->push_back(word_size[hWord->get_size(hWord)], hWord);
	}

	fclose(f_ptr);
	hWord->destroy((Item_ptr*)(&hWord));

	//START GAME//

	do{
		play_hangman(word_size);
	} 
	while (continue_play());

	//DESTROY DICTIONARY, END OF GAME
	for (i = 0; i < 50; i++){
		word_size[i]->destroy(&word_size[i]);
	}

	return 0;
}

void play_hangman(MY_VECTOR* word_size)
{
	int i, n, guesses;
	Node_ptr head = NULL;
	MY_STRING current_key = my_string_init_default();
	MY_STRING hWord = my_string_init_default();
	MY_STRING letters_geussed = my_string_init_default();
	MY_VECTOR temp_vector = my_vector_init_default(hWord->destroy, hWord->string_assignment);

	do{
		printf("What size word do you want to play with? ");
		scanf(" %d", &n);
		clear_keyboard_buffer();
	} while (n < 0 || n > 49 || word_size[n]->get_size(word_size[n]) == 0 || isalpha(n) );

	for (i = 0; i < word_size[n]->get_size(word_size[n]); i++)
		{
			temp_vector->push_back(temp_vector, ((MY_STRING)word_size[n]->at(word_size[n], i)));
		}

	do{
		printf("How many guesses would you like to have? ");
		scanf(" %d", &guesses);
		fflush(stdin);
	} while (guesses < 1 || isalpha(guesses));

	for (i = 0; i < n; i++){
		current_key->push_back(current_key, '-');
	}

	printf("\nCurrent key is: %s\n", current_key->c_str(current_key));
	i = 0;

	while (guesses > 0 && i < current_key->get_size(current_key)){
		printf("Number of guesses remaining: %d\n", guesses);
		head = NULL;

		process_guess(&temp_vector, &head, &current_key, &letters_geussed);
	
		printf("\nCurrent key is: %s\n", current_key->c_str(current_key));

		printf("Letters guessed so far: ");
		for (i = 0; i < letters_geussed->get_size(letters_geussed); i++)
		{
			printf("%c ", *(letters_geussed->at(letters_geussed, i)));
			
		}
			printf("\n");

		for (i = 0; i < current_key->get_size(current_key) && i > -1; i++)
		{
			if (*(current_key->at(current_key, i)) == '-'){
				i = -2;
			}
		}
		guesses--;
	}

	if (i == current_key->get_size(current_key))
	{
		printf("*****YOU WIN*****\n");
		printf("the word is: %s\n", current_key->c_str(current_key));
	}
	else
	{
		printf("*****YOU LOSE******\n");
		printf("The word I was thinking of was: %s\n", hWord->c_str((MY_STRING)temp_vector->at(temp_vector, rand() % temp_vector->get_size(temp_vector))));
	}

	current_key->destroy((Item_ptr*)&current_key);
	hWord->destroy((Item_ptr*)(&hWord));
	temp_vector->destroy(&temp_vector);
	letters_geussed->destroy((Item_ptr*)(&letters_geussed));
}

void process_guess(MY_VECTOR* word_bin, Node_ptr* pHead, MY_STRING* current_key, MY_STRING* letters_geussed)
{
	char guess;
	int i;
	int max_size = 0;
	MY_STRING temp_key = my_string_init_default();
	Node_ptr temp_node = NULL;

	printf("Number of possible words remaining: %d\n", (*word_bin)->get_size(*word_bin));
	do{
		printf("What is your guess? ");
		scanf(" %c", &guess);
		for (i = 0; i < (*letters_geussed)->get_size((*letters_geussed)); i++)
		{
			if (guess == *(*letters_geussed)->at(*letters_geussed, i))
			{
				i = (*letters_geussed)->get_size(*letters_geussed) + 2;
			}
		}

	} while (!isalpha(guess) || i > (*letters_geussed)->get_size((*letters_geussed)));

	for (i = 0; i < (*word_bin)->get_size(*word_bin); i++){
		temp_key = generate_key((MY_STRING)(*word_bin)->at((*word_bin), i), guess, temp_key);
		temp_node = search(*pHead, temp_key);

		if (temp_node != NULL){
			temp_node->string_bin->push_back(temp_node->string_bin, (*word_bin)->at(*word_bin, i));
		}
		else{
			*pHead = insert(*pHead, temp_key, (MY_STRING)(*word_bin)->at((*word_bin), i));
		}
	}

	temp_node = *pHead;

	print_tree(temp_node);

	find_largest_bin(*pHead, &temp_node, &max_size);

	*word_bin = temp_node->string_bin;
	temp_key = temp_node->string_key;

	for (i = 0; i < temp_key->get_size(temp_key); i++){
		if (*temp_key->at(temp_key, i) != '-'){
			printf("You guessed a correct letter!\n");
			break;
		}
	}

	if (i == temp_key->get_size(temp_key)){
		printf("Sorry, no %c in the word\n", guess);
	}

	(*letters_geussed)->push_back((*letters_geussed), guess);

	for (i = 0; i < temp_key->get_size(temp_key); i++){
		if (*(temp_key->at(temp_key, i)) != '-'){
			*(*current_key)->at(*current_key, i) = *(temp_key->at(temp_key, i));
		}
	}

	temp_key->destroy((Item_ptr*)&temp_key);
}

int continue_play(void)
{
	char c;

	do{
		printf("Do you wish to play another game? (Y/N)");
		scanf(" %c", &c);
	} while (c != 'Y' && c != 'N');

	if (c == 'Y'){
		return 1;
	}
	else{
		return 0;
	}
}

void clear_keyboard_buffer (void)
{
	char c;
	scanf("%c", &c);
	while(c != '\n')
	{
		scanf("%c", &c);
	}
	return;
}
