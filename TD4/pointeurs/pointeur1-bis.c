#include <stdio.h>

int main()
{
  int i = 3;
  int *p;

  i++;
  printf("*p = %d \n",*p);
  printf("Normalement vous ne devriez pas voir cette phrase\n");
}
