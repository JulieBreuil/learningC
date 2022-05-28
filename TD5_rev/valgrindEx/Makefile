all: valgrindEx

valgrindEx: valgrindEx.o
	gcc valgrindEx.o -o valgrindEx

valgrindEx.o: valgrindEx.c
	gcc -c valgrindEx.c -o valgrindEx.o

clean:
	rm -f valgrindEx