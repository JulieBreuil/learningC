#include <stdio.h>

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
  for (i = 0; i < 10; i++)
    printf("\ni = %d",i);
  printf("\n");
}