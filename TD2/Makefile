all : affichage

#etape 2 :edition de lien
#pour réaliser la cible affichage, je dois avoir la cible affichage.o (si je ne l'ai pas passer à la cible affichage.o)
#si deplus affichage.o est plus récente que le affichage que j'ai (cad que j'ai modifié 
#lefichier affichage.o depuis ma dernière edition de lien), je dois editier le lien
affichage : affichage.o
						gcc affichage.o -o affichage

#etape 1 : compilation
#pour réaliser la cible affichage.o, je dois avoir la cible affichage.c
#si deplus affichage.c est plus récente que le affichage.o que j'ai (cad que j'ai modifié lefichier affichage.c depuis ma dernière compilation), je dois recompiler
affichage.o : affichage.c
						gcc -c affichage.c -o affichage.o

clean :
						rm -f affichage.o
						rm -f affichage

