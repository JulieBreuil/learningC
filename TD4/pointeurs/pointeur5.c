#include <stdio.h>

int main()
{
 int i,j;
 i=3;
 j=i;
 fprintf(stdout,"L'entier i=%d est à l'adresse %p\n",i,&i);
 fprintf(stdout,"L'entier j=%d est à l'adresse %p\n",j,&j);

 return 0;
}
