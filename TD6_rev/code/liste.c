#include <stdio.h>
#include <stdlib.h>

#include "liste_type.h"
#include "liste.h"


/*!
************************************************
* \brief ajouter un element dans une liste triee
*    et renvoyer la newListe liste
* \param liste adresse d'une liste 
* \param val un entier a ajouter à la liste triee
* \return Modifie La liste, insère l'élément inséré
* \return retourne la newListe liste
**************************************************/    
LISTE insertionListeTriee (LISTE liste1, int val)
{
    LISTE newListe = (LISTE)malloc(sizeof(ELEMLISTE));
    if (liste1 == NULL){
        (*newListe).elem=val;
        newListe->suivant=NULL;
        return newListe;
    }
    else
    {
        if(liste1->elem<val)
        {
            liste1->suivant= insertionListeTriee(liste1->suivant,val);
            return liste1;
        }
        else
        {
            newListe->elem=val;
            newListe->suivant=liste1;
            return newListe;
        }
    }
}

/*!
************************************************
* \brief ajouter un element dans une liste triee
* \param pliste adresse d'une liste 
* \param val un entier a ajouter à la liste triee
* \warning On passe un pointeur sur une liste (donc un pointeur
*   sur un pointeur sur un element)
* \return Modifie La liste, insère l'élément inséré
**************************************************/    
void insertionListeTriee2 (LISTE *pliste, int val)
{
    *pliste = (LISTE)malloc(sizeof(ELEMLISTE));
    if (val>(*pliste)->elem){
        insertionListeTriee2(&((*pliste)->suivant),val);
        return;
    }else{
        (*pliste)->suivant=(*pliste);
        return;
    }
    //return;
}

/*!
************************************************
* \brief affiche une liste d'entier
* \param liste une liste d'entier
**************************************************/    
void afficherListe(LISTE liste)	
{
  ELEMLISTE *visitor;
 
 visitor=liste;
 while(visitor!=0)
   {
     fprintf(stdout,"|%d|",visitor->elem);
     visitor=visitor->suivant;
   }
 fprintf(stdout,"|--\n");
}

/*!
************************************************
* \brief vider une liste
* \param liste une liste d'entier
* \return le nombre d'entier suprrimés
**************************************************/
int viderListe(LISTE *pliste1);

/*! \brief program de test du module liste chainée
 */ 
 int main(int argc,char **argv)	
{
  LISTE liste1,liste2;

  fprintf(stdout,"/********** test rapide des fonctions de base *************\n");

  liste1=NULL;
  fprintf(stdout,"Listes triés créées avec insertionListeTriee\n");
  liste1=NULL;
  liste1=insertionListeTriee(liste1,1);
  liste1=insertionListeTriee(liste1,4);
  liste1=insertionListeTriee(liste1,5);
  liste1=insertionListeTriee(liste1,2);
  fprintf(stdout,"liste1:");
  afficherListe(liste1);
  fprintf(stdout,"Listes triés créées avec insertionListeTriee2\n");
  liste2=NULL;
  insertionListeTriee2(&liste2,2);
  insertionListeTriee2(&liste2,4);
  insertionListeTriee2(&liste2,7);
  insertionListeTriee2(&liste2,-1);
  fprintf(stdout,"liste2:");
  afficherListe(liste2);
}