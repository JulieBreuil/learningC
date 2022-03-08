#include <stdio.h>
#include <stdlib.h>

#define N 5

int produit_scalaire(int A[N], int B[N])
{
  int i, res;
  int *p1, *p2;
  // p1 a pour valeur l'adresse de la première case du tableau A 
  // p2 a pour valeur l'adresse de la première case du tableau B 
  p1 = A; p2 = B;
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
  //https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c/16595-creez-des-variables-grace-a-lallocation-dynamique#/id/r-16594
  A = malloc(N * sizeof(int));
  B = malloc(N * sizeof(int));
  if (A == NULL) {
    exit(0); //on arrête tout
  }
  if (B == NULL) {
    exit(0); //on arrête tout
  }
  // On demande de remplir les cases de A
  for (i = 0 ; i < N ; i++)
  {
      printf("Quel nb pour la case %d ? ", i + 1);
      scanf("%d", &A[i]);
  }
  // On demande de remplir les cases de B
  for (i = 0 ; i < N ; i++)
  {
      printf("Quel nb pour la case %d ? ", i + 1);
      scanf("%d", &B[i]);
  }

  // On affiche le tab A
  printf("\n\n A :\n");
  for (i = 0 ; i < N ; i++)
  {
      printf("%d ans\n", A[i]);
  }

  // On affiche le tab B
  printf("\n\n B :\n");
  for (i = 0 ; i < N ; i++)
  {
      printf("%d ans\n", B[i]);
  }


  printf("le produit scalaire vaut %d\n", produit_scalaire(A,B));

  return 0;
}
	 
