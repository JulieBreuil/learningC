#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "type_bigInt.h"
#include "util_bigInt.h"
#define DEBUG1

void  error(const char *mess)
{
  fprintf(stdout,"%s\n",mess);
  exit(-1);
}

bigInt initBigInt()
{
  bigInt bN;
  int i;

  bN=(bigInt)malloc(TAILLEMAX*sizeof(int));
  if (bN == NULL)
    {
      printf("Erreur malloc: plus de mémoire\n");
      exit(-1);
    }
  
  for (i=0; i<TAILLEMAX; i++)
    {
      bN[i]=0;
    }
  return(bN);
}

void zeroBigInt(bigInt bN)
{
  int i;

  for (i=0; i<TAILLEMAX; i++)
    {
      bN[i]=0;
    }
}

void freeBigInt(bigInt bN)
{
  free(bN);
}

/*!
************************************************
* \brief renvoie le nombre de chiffre d'un entier positif
* \param  N entier
* \result un entier positif
* \warning renvoie -1 pour l'entier 0
**************************************************/
int getNbChiffreInt(int N)
{
  int i=0,reste;
  
  if (N==0) return(0);

  reste=N;
  while(reste!=0)
    {
      reste=reste/10;
      i++;
    }
  return(i);
}


/*!
************************************************
* \brief renvoie le nombre de chiffre d'un Grand Entier
* \param  N bigInt
* \result un entier positif
* \warning renvoie -1 pour le Grand Entier 0
**************************************************/
int getNbChiffreBigInt(bigInt bN)
{
  int taille;
  
  //tu pars de la fin du tableau et tu remontes jusqu'au début. 
  //Voir formatage des nb deb p.51 du polyy
  //dès qu'une case est différente de 0, on s'arrête et après la boucle on compte cb de cases non vide il reste
  for (taille=TAILLEMAX-1; taille>=0; taille--)
    {
      if (bN[taille]!=0) break;
    }

  // '0' a 0 chiffres
  if (taille==-1) return(0);
  else return(taille+1);
}

/*!
************************************************
* \brief Affiche un grand entier à l'écrant
* \param  bN bigInt
**************************************************/
void printBigInt(bigInt bN)
{int i,taille,warning=0;

  taille=getNbChiffreBigInt(bN);

    
 if (taille==0)
   {
     fprintf(stdout,"0\n");
   }
 else
   {
     for (i=taille-1; i>=0; i--)
       {
	 if (bN[i]>=10)
	   {
	     warning=1;
	     fprintf(stdout,"'%d'",bN[i]);
	   }
	 else
	   fprintf(stdout,"%d",bN[i]);

       }
     fprintf(stdout,"\n");
     if (warning==1) fprintf(stdout,"Warning some digit are greater than 10 !!!\n");
   }
}


/*!
************************************************
* \brief imprime un grand entier à dans une chaine de caractère (fait le malloc)
* \param  bN bigInt
**************************************************/
char* sprintBigInt(bigInt bN)
{
  int i,taille;
  char *res;

  taille=getNbChiffreBigInt(bN);
  res=(char *)malloc(taille+1);
    
 if (taille==0)
   {
     sprintf(res,"0");
   }
 else
   {
     res[taille]=0;
     for (i=taille-1; i>=0; i--)
       {
	 res[taille-1-i]=48+bN[i]; //conversion en code ASCII pour chaine de caractère
       }
   }
 return res;
}





/*!
************************************************
* \brief Copie le bigInt src dans le bigInt dest, 
*        les bigInt etant déjà alloué
* \param  src bigInt
* \param  dst bigInt
* \warning renvoie -1 pour le Grand Entier 0
**************************************************/
void copyBigInt(bigInt src,bigInt dst)
{
  int i;
  
  for (i=0;i<TAILLEMAX;i++)
    {
      dst[i]=src[i];
    }
}


/*!
************************************************
* \brief Teste l'équalité de deux bigInt
* \param  bN1 bigInt
* \param  bN2 bigInt
* \result renvoie 0 si ils sont différents 1 si ils sont égaux
**************************************************/
int bigIntEqualQ(bigInt bN1,bigInt bN2)
{
  int i;
  
  for (i=0;i<TAILLEMAX;i++)
    {
      if (bN1[i]!=bN2[i]) return 0;
    }
  return 1;
}


/*!
************************************************
* \brief traduit un Grand Entier (inférieur à 2^31) en
*  l'entier correspondant
* \param  N bigInt
* \result un entier positif
* \warning provoque une erreur en cas de débordement
* ************************************************/
int bigIntToInt(bigInt bN)
{
  int res,i,taille,puiss;

  res=bN[0];
  taille=getNbChiffreBigInt(bN);
  i=1;
  puiss=10;
  while ((i<taille)&&(i<=9))  // TODO: test d'overflow
    {
      res= res+puiss*bN[i];
      i++;
      puiss=puiss*10;
    }
  if (i<taille) 
    {
      error("Overflow bigInToInt");
    }
  return(res);
}

/*!
************************************************
* \brief traduit un entier en le Grand Entier
* \param  N entier
* \param  bN un Grand Entier (déjà alloué)
* ************************************************/
void intToBigInt(int N,bigInt bN)
{
  int reste, taille, i;

  reste=N;
  taille=getNbChiffreInt(reste);

  if (N>=0)
    {
     for (i=0; i<=taille; i++)
       {
	 bN[i]=reste%10;
	 reste=reste/10;
       }
    }

 }


/*!
************************************************
* \brief traduit un entier en le Grand Entier
* \param  N_s chaine de caractère représentant un grand entier
* \param  bN un Grand Entier (déjà alloué)
* ************************************************/
void stringToBigInt(char *N_s,bigInt bN)
{
  int taille,i;

  taille=strlen(N_s);

  if (taille>=0)
    {
     for (i=0; i<taille; i++)
       {
	 bN[taille-i-1]=N_s[i]-48;
       }
    }

 }


