all : scannage

#etape 2 :edition de lien
#pour réaliser la cible scannage, je dois avoir la cible scannage.o (si je ne l'ai pas passer à la cible scannage.o)
#si deplus scannage.o est plus récente que le scannage que j'ai (cad que j'ai modifié 
#lefichier scannage.o depuis ma dernière edition de lien), je dois editier le lien
scannage : scannage.o
						gcc scannage.o -o scannage

#etape 1 : compilation
#pour réaliser la cible scannage.o, je dois avoir la cible scannage.c
#si deplus scannage.c est plus récente que le scannage.o que j'ai (cad que j'ai modifié lefichier scannage.c depuis ma dernière compilation), je dois recompiler
scannage.o : scannage.c
						gcc -c scannage.c -o scannage.o

clean :
						rm -f scannage.o
						rm -f scannage