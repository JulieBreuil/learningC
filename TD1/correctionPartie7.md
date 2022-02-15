### bibilothèques en C
Makefile

al: libpgcd.a

pgcd.o : pgcd.c
        gcc -Wall pgcd.c -c  -o pgcd.o

libpgcd.a:  pgcd.o
        ar -crs libpgcd.a pgcd.o

clean:
        rm -f pgcd *.à *.a *~