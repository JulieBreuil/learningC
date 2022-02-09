#include <stdio.h>
#include "hello.h"

int main()
{
    int erreur;

    erreur = hello();

    if (erreur!=0)
        printf("error in hello \n");

    return(0);
}