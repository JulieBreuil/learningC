all : fonction

#etape 2 :edition de lien
#pour réaliser la cible fonction, je dois avoir la cible fonction.o (si je ne l'ai pas passer à la cible fonction.o)
#si deplus fonction.o est plus récente que le fonction que j'ai (cad que j'ai modifié 
#lefichier fonction.o depuis ma dernière edition de lien), je dois editier le lien
fonction : fonction.o
						gcc fonction.o -o fonction

#etape 1 : compilation
#pour réaliser la cible fonction.o, je dois avoir la cible fonction.c
#si deplus fonction.c est plus récente que le fonction.o que j'ai (cad que j'ai modifié lefichier fonction.c depuis ma dernière compilation), je dois recompiler
fonction.o : fonction.c
						gcc -c fonction.c -o fonction.o

clean :
						rm -f fonction.o
						rm -f fonction