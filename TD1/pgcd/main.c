#include <stdio.h>
#include "pgcd.h"

int main()
{
    int erreur;

    int a = 2;
    int b = 6;

    erreur = pgcd(a,b); //pgcd est une fonction

    printf("%d\n",erreur);

    return(0);
}