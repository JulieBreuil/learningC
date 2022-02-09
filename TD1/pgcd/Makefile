all: main
  
main: main.o pgcd.o
		gcc main.o pgcd.o -o main

pgcd.o: pgcd.c pgcd.h
		gcc -c pgcd.c -o pgcd.o

main.o: main.c pgcd.h
		gcc -c main.c -o main.o

clean :
		rm -f main *.o