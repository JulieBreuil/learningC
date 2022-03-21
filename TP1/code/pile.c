#include <stdio.h>
#include <stdlib.h>
#include "pile.h"


/************************************************
* \brief  affiche l'erreur et quitte le programme 
* \param message une chaine de caractère à afficher avant de quitter
**************************************************/    
int error1(char *message){
      printf(message);
      return 0; //quitte le programme
}

/************************************************
* \brief     ajoute l'élément elem au sommet de la pile pile
* \param pile est la pile 
* \param elem L'élément à rajouter au sommet de pile
* \result La fonction renvoie la pile modifiée
**************************************************/    
PILE Empiler (PILE pile, int elem){
    PILE pile1=NULL;
    pile1 = malloc(sizeof(*pile1));   
    (*pile1).elem = elem;
    (*pile1).suivant = pile;
    return pile;
}

/************************************************
* \brief affiche une pile d'entier
* \param liste une liste d'entier
**************************************************/    
void afficherPile (PILE pile){
    
    //le type PILE est un pointeur vers un type ELEMPILE
    //il y a des priorités, le point est plus prioritaire que le *
    pile = malloc(sizeof(*pile));   
    printf("%d\n",(*pile).elem);
    //même chose, mais en raccourci
    //printf("%d\n",pile->elem);

    
    printf("test2\n");
    afficherPile(pile->suivant);

}


