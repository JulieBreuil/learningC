#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"

ARBRE creerArbre(int val, ARBRE filsGauche, ARBRE filsDroit)
{
    NOEUD *unArbre = (NOEUD *)malloc(sizeof(NOEUD));
    (*unArbre).val = val;
    (*unArbre).filsGauche = filsGauche;
    (*unArbre).filsDroit = filsDroit;
    return unArbre;
}

void afficheArbre(ARBRE unArbre)
{
    printf("La valeur courante est %d \n",unArbre->val);
    if (unArbre->filsGauche != NULL)
    {
        afficheArbre(unArbre->filsGauche);
    }
    if (unArbre->filsDroit != NULL)
    {
        afficheArbre(unArbre->filsDroit);
    }
}

int max(int a, int b)
{
    if (a>b)
    {
        return a;
    }
    return b;
}

int hauteurArbre(ARBRE unArbre)
{
    if (unArbre!=NULL)
    {
        return 1+max(hauteurArbre(unArbre->filsGauche),hauteurArbre(unArbre->filsDroit));
    }
    return 0;
}