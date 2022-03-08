#include <stdio.h>

int main()
{
  int i = 3, j = 6;
  int *p1, *p2;

  p1 = &i;
  p2 = &j;
  *p1 = *p2;
}
