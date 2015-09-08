CC = gcc
CFLAGS = -g -Wall --std=c99

main: main.o my_string.o my_vector.o AVL_tree.o
	$(CC) -o main main.o my_string.o my_vector.o AVL_tree.o
main.o: main.c my_string.h my_vector.h AVL_tree.h status.h
	$(CC) $(CFLAGS) -c -o main.o main.c
my_string.o: my_string.c my_string.h status.h
	$(CC) $(CFLAGS) -c -o my_string.o my_string.c
my_vector.o: my_vector.c my_vector.h status.h
	$(CC) $(CFLAGS) -c -o my_vector.o my_vector.c
AVL_tree.o: AVL_tree.c AVL_tree.h my_vector.h my_string.h status.h
	$(CC) $(CFLAGS) -c -o AVL_tree.o AVL_tree.c

unit_test: my_string.o unit_test.o test_def.o
	$(CC) -o unit_test unit_test.o my_string.o test_def.o
unit_test.o: unit_test.c my_string.h unit_test.h
	$(CC) $(FLAGS) -c -o unit_test.o unit_test.c
test_def.o: test_def.c unit_test.h my_string.h
	$(CC) $(CFLAGS) -c -o test_def.o test_def.c

