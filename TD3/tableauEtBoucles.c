#include <stdio.h>
#define N 5 //c'est comme si on définissait une variable globale fixée. Dans tout le pgrm N sera égale à 5

int produit_scalaire(int A[N], int B[N]){
  //QUESTION 4
  int res = 0;
  int i;
  for (i=0;i<5;i++){
    res=res+(A[i]*B[i]);
    printf("%d\n",res);
  }
  return res;  
}

int main()
{
  //QUESTION 1
  /*Nous écrirons un programme avec un tableau lorsque nous aurons vu les boucles
  for (prochaine question). Combien à d’élément et quel est l’index du dernier élément du tableau
  tab définit ainsi :
  char tab[1024]*/
  //index = 1023

  //QUESTION 2
  //cf le pdf TD3
  /*Addition
  +
  Soustraction
  -
  Multiplication
  *
  Division
  /
  Modulo
  %*/

  //QUESTION 3
  int i = 0;
  while (i!=15){
    printf("3*5=");
    scanf("%d",&i);
  }
  printf("3*5 = %d\n",i);

  //TEST BOUCLE FOR
  int j;
  for (j = 0; j < 10; j++)
    printf("\nj = %d",j);
  printf("\nj = %d",j);
  printf("\n");

  //QUESTION 4
  int A[5]={1,2,3,4,5};
  int mon_prod_sca = produit_scalaire(A,A);
  printf("%d\n",mon_prod_sca);  
}