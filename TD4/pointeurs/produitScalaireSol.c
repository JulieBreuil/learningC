#include <stdio.h>

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
  int A[N]={1,1,1,1,1};
  int B[N]={1,1,1,1,1};

  printf("le produit scalaire vaut %d\n", produit_scalaire(A,B));

  return 0;
}
	 
