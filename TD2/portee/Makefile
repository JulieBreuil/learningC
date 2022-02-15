all : portee

#etape 2 :edition de lien
#pour réaliser la cible portee, je dois avoir la cible portee.o (si je ne l'ai pas passer à la cible portee.o)
#si deplus portee.o est plus récente que le portee que j'ai (cad que j'ai modifié 
#lefichier portee.o depuis ma dernière edition de lien), je dois editier le lien
portee : portee.o
						gcc portee.o -o portee

#etape 1 : compilation
#pour réaliser la cible portee.o, je dois avoir la cible portee.c
#si deplus portee.c est plus récente que le portee.o que j'ai (cad que j'ai modifié lefichier portee.c depuis ma dernière compilation), je dois recompiler
portee.o : portee.c
						gcc -c portee.c -o portee.o

clean :
						rm -f portee.o
						rm -f portee