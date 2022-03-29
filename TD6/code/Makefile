CFLAGS	+= -Wall   -g 
LDFLAGS += -Wall

all: liste

liste.o: liste.c liste.h liste_type.h
	gcc ${CFLAGS} -c liste.c -o liste.o 

liste:  liste.o
	gcc ${LDFLAGS}  liste.o -o liste

liste_corr: liste_corr.c liste.h liste_type.h
	gcc ${CFLAGS}  liste_corr.c -o liste_corr 

tarSol: clean 
	cd ..; tar -cvf TD-liste-Sol.tar code/

tar: clean 
	cd ..; tar -cvf TD-liste.tar --exclude code/liste_corr.c code/ 

clean:
	-rm -rf *~ *.out  *.o liste liste_corr


