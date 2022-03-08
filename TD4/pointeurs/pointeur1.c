#include <stdio.h>

int main()
{
  int i = 3;
  int *p;

  p = &i;

  printf("*p = %d \n",*p);
  printf("p = %p \n",p);
}
