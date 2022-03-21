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
    return pile1;
}

/************************************************
* \brief    Retire l'element du sommet de la pile pointée par ppile et renvoie 
   sa valeur. 
* \param ppile un pointeur vers la pile 
* \result Le résultat de la fonction est la 
	  valeur de l'élément supprimé si aucune erreur n'est intervenue
          La pile pointée par ppile a été modifiée: son premier 
          élément a été supprimé (le deuxième élément est donc devenu 
	  le sommet de pile). 
* \remark    Si la pile pointé par ppile est vide, la fonction affiche une erreur et interrompt le programme.
**************************************************/    
int Depiler(PILE* ppile){
    //ppile pointe vers une PILE
    //une PILE pointe vers une ELEMPILE
    
    //on défiinit pile dont le pointeur est ppile
    PILE pile;
    pile = *ppile;

    //pile pointe vers le second élément, et non plus le premier
    pile = pile -> suivant;

    //permet de libérer la mémoire qui était allouée au premier élément
    free(*ppile);

    //on modifie ppile en fonction de pile
    *ppile = pile;
}	

/************************************************
* \brief affiche une pile d'entier
* \param liste une liste d'entier
**************************************************/    
void afficherPile (PILE pile){
    
    //le type PILE est un pointeur vers un type ELEMPILE
    //il y a des priorités, le point est plus prioritaire que le *
    printf("%d\n",(*pile).elem);
    //même chose, mais en raccourci
    //printf("%d\n",pile->elem);

    if (pile->suivant == NULL){
        printf("Fin de l'affichage\n");
    }else{
        afficherPile(pile->suivant);
    }     
}


