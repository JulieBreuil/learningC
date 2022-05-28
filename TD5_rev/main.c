#include <stdio.h>
#include "arbre.h"

int main()
{
    int val = 3;
    int vol = 8;
    int vil = 9;
    ARBRE a = NULL;
    ARBRE b = NULL;
    ARBRE monArbre = creerArbre(val,a,b);
    ARBRE monArbre2 = creerArbre(vol,a,b);
    ARBRE monArbre3 = creerArbre(vil,monArbre,monArbre2);
    ARBRE monArbre4 = creerArbre(vil,monArbre3,monArbre2);
    printf("Mon abre a pour valeur %d\n", monArbre->val);
    afficheArbre(monArbre3);
    int h= hauteurArbre(monArbre4);
    printf("Mon arbre a une hauteur de %d\n",h);
}