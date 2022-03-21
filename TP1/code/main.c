#include <stdio.h>

#include "pile.h"
#include "hanoi.h"

#define N 9
 
/*!***********************************************
* \brief  Programme de test des fonction du module pile.c
**************************************************/    

int main(int argc,char **argv)	
{
  PILE pile1=NULL;
  int val,i;

  fprintf(stdout,"/********** test de pile d'entier *************\n");

  for (i=N;i>0;i--)
    {
      val=i;
      pile1=Empiler(pile1,val);
    }
  fprintf(stdout,"après mise en place d'une pile de taille %d\n",N);
  afficherPile(pile1);

  Depiler(&pile1);
  fprintf(stdout,"/**** après dépilation **\n");
  afficherPile(pile1);


  fprintf(stdout,"/**** fin du programme de test de pile d'entier **\n");

  fprintf(stdout,"/********** test de la fonction deplacer de Hanoi *************\n");

  //creation pile (1 2 3)
  PILE pile2=NULL;
  int vol,j;
  for (j=3;j>0;j--)
    {
      vol=j;
      pile2=Empiler(pile2,vol);
    }

  //creation pile (4)
  PILE pile3=NULL;
  pile3=Empiler(pile3,4);

  fprintf(stdout,"/********** piles avant déplacement *************\n");
  afficherPile(pile2);
  afficherPile(pile3);

  //deplacement du sommet de la pile2 à la pile3
  //PILE *psource = &pile2;
  //PILE *pdest = &pile3;
  deplacer(&pile2, &pile3);
  fprintf(stdout,"/********** piles après déplacement *************\n");
  afficherPile(pile2);
  afficherPile(pile3);

  fprintf(stdout,"/********** test de Hanoi *************\n");
  PILE passage=NULL;
  PILE depart=NULL;
  PILE arrive=NULL;
  int M=5;
  
  //creation pile depart
  int vil,k;
  for (k=M;k>0;k--)
    {
      vil=k;
      depart=Empiler(depart,vil);
    }
  
  fprintf(stdout,"/********** piles avant Hanoi *************\n");
  printf("pile de depart : \n");
  afficherPile(depart);
  printf("pile de passage : \n");
  afficherPile(passage);
  printf("pile d'arrivee' : \n");
  afficherPile(arrive);

  hanoi(&depart, &passage, &arrive, M);

  fprintf(stdout,"/********** piles apres Hanoi *************\n");
  printf("pile de depart : \n");
  afficherPile(depart);
  printf("pile de passage : \n");
  afficherPile(passage);
  printf("pile d'arrivee' : \n");
  afficherPile(arrive);

  return 0;
}