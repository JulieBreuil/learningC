#include <stdio.h>
#include <stdlib.h>

#define N 5

int produit_scalaire(int A[N], int B[N])
{
  int i, res;
  int *p1, *p2;
  p1=A;
  p2=B;
  // p1 a pour valeur l'adresse de la première case du tableau A
  // p2 a pour valeur l'adresse de la première case du tableau B

  res=0;
  for (i=0;i<N;i++)
    {
      res += *p1 * *p2;
      p1++;
      p2++;
    }
  return res;
}

int main()
{
  int i;
  int* A=NULL;
  int* B=NULL;
  int nbDeCases=0;

  //On demande le nb de cases à l'utilisateur
  printf("Combien de cases voulez-vous ? ");
  scanf("%d", &nbDeCases);

  if (nbDeCases>0)
  {
      A=malloc(nbDeCases * sizeof(int)); //on alloue de la mémoire pour le tableau
      B=malloc(nbDeCases * sizeof(int)); //on alloue de la mémoire pour le tableau
      if ((A == NULL) || (B == NULL)) //On vérifie si l'alloc a marché ou non
      {
          exit(0); //on arrête tout
      }

      //On demande la valeur des cases une à une du tableau A
      for (i=0;i<nbDeCases;i++)
      {
          printf("Quel valeur pour la case %d du tableau A ? ", i + 1);
          scanf("%d", &A[i]);
      }

      //On demande la valeur des cases une à une du tableau B
      for (i=0;i<nbDeCases;i++)
      {
          printf("Quel valeur pour la case %d du tableau B ? ", i + 1);
          scanf("%d", &B[i]);
      }
  }

  //int A[N]={1,1,1,1,1};
  //int B[N]={1,1,1,1,1};

  printf("le produit scalaire vaut %d\n", produit_scalaire(A,B));

  return 0;
}
	 
