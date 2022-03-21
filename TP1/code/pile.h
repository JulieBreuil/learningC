#ifndef pile_h_
#define pile_h_

#include "pile_type.h"

/************************************************
* \brief  affiche l'erreur et quitte le programme 
* \param message une chaine de caractère à afficher avant de quitter
**************************************************/    
int error1(char *message);	


/************************************************
* \brief     ajoute l'élément elem au sommet de la pile pile
* \param pile est la pile 
* \param elem L'élément à rajouter au sommet de pile
* \result La fonction renvoie la pile modifiée
**************************************************/    
PILE Empiler (PILE pile, int elem);


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
int Depiler(PILE* ppile);	

/************************************************
* \brief affiche une pile d'entier
* \param liste une liste d'entier
**************************************************/    
void afficherPile (PILE pile);

#endif
