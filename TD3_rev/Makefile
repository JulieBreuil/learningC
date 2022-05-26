all: boucle

boucle: boucle.o
	gcc boucle.o -o boucle

boucle.o: boucle.c
	gcc -c boucle.c -o boucle.o

clean:
	rm -f boucle