CFLAGS+= -std=c99 -O3 -Werror -Wall -pedantic -g
CC= clang

all:
	clear
	$(CC) $(CFLAGS) tree.c -o tree
	$(CC) $(CFLAGS) input.c -o input
	./input
	./tree

size:
	clear
	$(CC) $(CFLAGS) tree.c -o tree
	$(CC) $(CFLAGS) input.c -o input
	./input LENGHT= 50 MAX= 100
	./tree
