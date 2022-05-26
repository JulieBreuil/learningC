#include <stdio.h>

int main()
{
  int i = 3;
  int *p;

  p = &i;

  printf("i = %d \n",i);
  printf("&i = %p \n",&i);
  printf("*p = %d \n",*p);
  printf("p = %p \n",p);
}
