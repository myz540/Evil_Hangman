Brett Lundy and Mike Zhong first created a working build of the evil_hangman game
using a linked list implementation. Once we had the main function working,
we implemented the AVL_tree.c and tested it independently of main. 
Once we were confident the AVL tree was working properly, we included it in
main and it worked without any problems. A lot of the variable names are still
head and pHead, since they carried over from the linked list implementation
with no problem. Our linked list implementation has no memory leaks but we
figured it would be more beneficial to turn in the AVL tree implementation
with memory leaks rather than the linked list implementation without. A 'B' is
better than a 'C'. 

The program has memory leaks associated with the AVL tree. Main calls the function
play_hangman which does the bulk of the heavy lifting. In play_hangman, the function
process_guess is called several times. Each time process_guess is called, the user
is prompted to enter their guess and an AVL tree is built by iterating through the
word bin of the user's chosen size. Each word in the bin generates a key, if the key
is unique, we add a node to the tree, use string_assignment to assign that key to 
the node, and use vector push_back to add the given word to that node's word bin. If
the key is not unique, we simply push_back the word into that node's word bin.

Ideally, at the end of each iteration of process_guess, the AVL tree should be destroyed
and its MY_STRING key and MY_VECTOR word_bin freed up. We were either  unable to get our 
destroy_tree function to work correctly, or we were calling it in the wrong place. Either 
way, the tree is not destroyed. When we called destroy_tree at the end of process_guess,
we got a segmentation fault and were unable to determine what was causing the program
to crash. In the end, we have memory leaks associated with the AVL tree, but we were able
to properly manage all memory associated with MY_STRING and MY_VECTOR variables outside
of the nodes of the tree. If we had more time, we may have been able to turn in a
more polished product but as it stands, our program works but has memory leaks associated
with every call to process_guess, which makes several calls to insert.
