### bibilothèques en C
Makefile

all: libpgcd.a

pgcd.o : pgcd.c
        gcc -Wall pgcd.c -c  -o pgcd.o

libpgcd.a:  pgcd.o
        ar -crs libpgcd.a pgcd.o

clean:
        rm -f pgcd *.à *.a *~


Makefile
all: main

main: main.o
        gcc -Wall -L ../libPGCD/ main.o -o main -lpgcd

main.o: main.c
        gcc Wall -I ../libPGCD/ main.c -c -o main.o

clean:
        rm -f main *.o *~