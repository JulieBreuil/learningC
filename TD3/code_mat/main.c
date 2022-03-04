#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matrice.h"
#include "utilMatrice.h"
#include "matProd.h"
	
//QUESTION 6
/* la commande make, exécutez le programme produit. Comprenez vous ce
qu’il se passe ?
— étudiez les différents fichiers .c et .h ainsi que le Makefile, pourquoi la compilation du
fichier main.c dépend-t’elle du fichier matrice.h ? et utilMatrice.h ?
Les fichiers .h contiennent des méthodes qui correspondent au fichier .c du même nom
Quand on fait inculude fichier.h dans main.c , on a alors inclu toutes les méthodes de fichier.c dans main.c

— à quoi servent les macro #ifndef dans le fichier matrice.h ?
voir le fichier matrice.h

— Pourquoi ces valeurs bizarres s’affichent lors de l’affichage du résultat C=AB.
— Pourquoi n’avons nous pas proposé une fonction qui retourne une matrice ?
— Pourquoi peut-on modifier la matrice C avec la fonction matProd alors que l’on a vu que l’on
passait les paramêtres par valeur ?
— Ecrivez un nouvelle fonction int matEqualQ(int A[N][N], int B[N][N]) qui vérifie
que deux matrices sont équales.
— Validez votre fonction matProd en testant l’égalité avec la matrice solution proposée (matriceAxB.txt).*/

int  main(int argc,char *argv[])
{
  FILE *fichA, *fichB;
  char nomFichA[15]="matriceA.txt";
  char nomFichB[15]="matriceB.txt";

  int A[N][N], B[N][N], C[N][N];
  int err;
  
  //ouverture fichier A
  fichA=fopen(nomFichA,"r");
  if (!fichA)
    {
      fprintf(stderr,"erreur d'ouverture du fichier %s\n",nomFichA);
      exit(-1);
    }

  //ouverture fichier B
  fichB=fopen(nomFichB,"r");
  if (!fichB)
    {
      fprintf(stderr,"erreur d'ouverture du fichier %s\n",nomFichB);
      exit(-1);
    }
  
  err=lireMatrice(fichA,A);
  if (err)
    {
      fprintf(stderr,"erreur lors de la lecture de %s\n",nomFichA);
      exit(-1);
    }

  err=lireMatrice(fichB,B); 
  if (err)
    {
      fprintf(stderr,"erreur lors de la lecture de %s\n",nomFichB);
      exit(-1);
    }

 fprintf(stdout," Matrice lues: \n");
 fprintf(stdout," A: \n");
 ecrireMatrice(stdout,A);

 fprintf(stdout," B: \n");
 ecrireMatrice(stdout,B);

 matProd(A,B,C);

 fprintf(stdout," resultat du produit C=AB (FAUX évidement): \n");
 ecrireMatrice(stdout,C);
 
 
   return(0);
}
