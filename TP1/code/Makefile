all : main

pile.o : pile.c pile.h pile_type.h

						gcc pile.c -c -o pile.o

main.o : main.c
						gcc -c main.c -o main.o

main : main.o pile.o

						gcc pile.o main.o -o main

clean :
						rm -f pile main *.o	