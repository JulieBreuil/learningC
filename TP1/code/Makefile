all : main

pile.o : pile.c pile.h pile_type.h
						gcc pile.c -c -o pile.o

hanoi.o : hanoi.c hanoi.h pile_type.h pile.h
						gcc hanoi.c -c -o hanoi.o

main.o : main.c
						gcc -c main.c -o main.o

main : main.o pile.o hanoi.o

						gcc pile.o main.o hanoi.o -o main

clean :
						rm -f pile hanoi main *.o	