#include <stdio.h>
#include <stdlib.h>


#include "type_bigInt.h"
#include "util_bigInt.h"
#include "io_bigInt.h"

#define DEBUG1

/*!
************************************************
* \brief lit un bigInt dans un fichier, jusqu'à un espace ou EOF
* \param  fich FILE *
* \param  res Le bigInt Lu (alloué avant l'appel)
* \result un entier (0 si pas d'erreur)
**************************************************/
int readBigInt(FILE *fich,bigInt res)
{
  int i=0, chiffre,taille;
  bigInt temp;

  temp=initBigInt();
  zeroBigInt(res);

  chiffre=fgetc(fich);
  while ((((char)chiffre==' ')  || ((char)chiffre=='\n')) && 
	 ((char)chiffre!=EOF))
    chiffre=fgetc(fich);
  while (((char)chiffre!=' ') && ((char)chiffre!=EOF) && 
	 ((char)chiffre!='\n'))
    {
      temp[i]=(char)chiffre-'0';
      i++;
      if (i>TAILLEMAX) 
	{
	  fprintf(stdout,"Error readBigInt, int too large \n");
	  exit(-1);
	}
      chiffre=fgetc(fich);
    }
  taille=i;
  // temps est écrit dans le mauvais sens
  for (i=taille-1;i>=0;i--)
    {
      res[taille-i-1]=temp[i];
    }
  freeBigInt(temp);
  return(chiffre);
}

/*!
************************************************
* \brief ecrit un bigInt dans un ficher, termine par un espace
* \param  fich FILE *
* \param  res Le bigInt écrit
* \result un entier (0 si pas d'erreur)
**************************************************/
int writeBigInt(FILE *fich, bigInt bN)
{
  int i=0,chiffre;

  i=getNbChiffreBigInt(bN)-1;
 
  while (i>=0)
    {
      chiffre=bN[i];
      fprintf(fich,"%d",chiffre);
      i--;
    }
  fprintf(fich,"%c",' ');
  return(0);
}

