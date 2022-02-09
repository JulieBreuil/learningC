all : hello
  
#etape 2 :edition de lien
#pour réaliser la cible hello, je dois avoir la cible hello.o (si je ne l'ai pas passer à la cible hello.o)
#si deplus hello.o est plus récente que le hello que j'ai (cad que j'ai modifié 
#lefichier hello.o depuis ma dernière edition de lien), je dois editier le lien
hello : hello.o
						gcc hello.o -o hello

#etape 1 : compilation
#pour réaliser la cible hello.o, je dois avoir la cible hello.c
#si deplus hello.c est plus récente que le hello.o que j'ai (cad que j'ai modifié lefichier hello.c depuis ma dernière compilation), je dois recompiler
hello.o : hello.c
						gcc -c hello.c -o hello.o

clean :
						rm -f hello.o
						rm -f hello


