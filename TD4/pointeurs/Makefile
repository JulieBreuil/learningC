CFLAGS = -g -Wall -DDEBUG 
LDFLAGS =  -Wall
SOURCE = pointeur1.c pointeur2.c pointeur3.c pointeur1-bis.c
OBJECT = $(SOURCE:.c=.o) #variable dynamique pour avoir les noms des .o
TARGET = $(SOURCE:.c=)
HEADER = $(wildcard *.h) #wildcard récupère tous les fichiers .h du repertoire
.PRECIOUS: $(OBJECT) #indication à make de ne pas supprimer les .o intermédiaire

all:  $(TARGET)


%: %.o $(HEADER)
	gcc  ${LDFLAGS} $< -o $@

%.o: %.c
	gcc ${CFLAGS} -c $< -o $@


tar: clean
	cd ..; tar cvf  TD4-code.tar code/pointeur*.c code/Makefile code/produitScalaireSol.c

tar-sol: clean
	cd ..; tar cvf  TD4-sol.tar code/pointeur*.c code/Makefile code/produitScalaireSol.c code/produitScalairePointeurSol.c code/sol-pointeur3.c


clean: 
	\rm -rf *.o $(TARGET)  *~ a.out sol-pointeur2 sol-pointeur3
