all : affichage scannage fonction portee flottant
affichage : affichage.o
						gcc affichage.o -o affichage

affichage.o : affichage.c
						gcc -c affichage.c -o affichage.o

scannage : scannage.o
						gcc scannage.o -o scannage

scannage.o : scannage.c
						gcc -c scannage.c -o scannage.o

fonction : fonction.o
						gcc fonction.o -o fonction

fonction.o : fonction.c
						gcc -c fonction.c -o fonction.o

portee : portee.o
						gcc portee.o -o portee

portee.o : portee.c
						gcc -c portee.c -o portee.o

flottant : flottant.o
						gcc flottant.o -o flottant

flottant.o : flottant.c
						gcc -c flottant.c -o flottant.o


clean :
						rm -f affichage scannage fonction portee flottant *.o						