all: main
  
main: main.o hello.o
		gcc main.o hello.o -o main

hello.o: hello.c hello.h
		gcc -c hello.c -o hello.o

main.o: main.c hello.h
		gcc -c main.c -o main.o

clean :
		rm -f main *.o


