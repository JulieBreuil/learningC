all: main

main: main.o arbre.o
	gcc main.o arbre.o -o main

arbre.o: arbre.c arbre.h arbre_type.h
	gcc -c arbre.c -o arbre.o

main.o: main.c arbre.h arbre_type.h
	gcc -c main.c -o main.o

clean:
	rm -f arbre