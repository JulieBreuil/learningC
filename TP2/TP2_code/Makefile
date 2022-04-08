CFLAGS+=-Wall -g 
LDFLAGS+=-Wall -g  

OBJ=io_bigInt.o util_bigInt.o bigInt.o 
SRC=$(OBJ:=.c)
INCLUDES=*.h

all: testUtils testBigInt main 


main: $(OBJ) $(INCLUDES) main.o 
	gcc  $(OBJ) main.o -o $@

testBigInt: $(OBJ) $(INCLUDES) testBigInt.o main_testBigInt.o
	gcc  $(OBJ) testBigInt.o main_testBigInt.o -o $@

testUtils: $(OBJ) $(INCLUDES) testUtils.o main_testUtils.o
	gcc  $(OBJ) testUtils.o main_testUtils.o -o $@

%.o: %.c $(INCLUDES)
	gcc  $(CFLAGS) -c $<  -o $@

valgrind: $(EXE)
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./$(EXE)

tar-sol:clean
	cd ..;tar cvf TP2.tar code/*.c code/*.h code/Makefile code/*.txt

#for students, add and modify bigInt.c
tar:	clean
	\rm  -rf TP2_code
	mkdir -p TP2_code
	cp io_bigInt.c util_bigInt.c testUtils.c testBigInt.c  \
	main_testBigInt.c main_testUtils.c main.c *.h Makefile \
	dataTestAdd.txt dataTestFactorielle.txt dataTestMul.txt TP2_code 
	cp bigInt_students.c TP2_code/bigInt.c
	tar cvf ../TP2_code.tar TP2_code

generateTest: $(OBJ) generateTest.o
	gcc  $(OBJ) generateTest.o -o $@

dummy:	

clean:
	-rm -f *~ *.out  *.o *.old main testUtils testBigInt

