#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "type_bigInt.h"
#include "util_bigInt.h"
#include "io_bigInt.h"
#include <stdbool.h>

#define DEBUG1



/*!
************************************************
* \brief Additionne deux Grands Entiers
* \param  bN1 Grand Entier
* \param  bN2 Grand Entier
* \param  res le Grand Entier résultat
* \return  0 si l'addition est OK, 1 en cas d'overflow
* \warning res doit être déjà alloué,
* ************************************************/
int addBigInt(bigInt bN1,bigInt bN2,bigInt res)
{
  bool retenue = false;
  int longbN1 = getNbChiffreBigInt(bN1);
  int longbN2 = getNbChiffreBigInt(bN2);
  int longAdd;
  if (longbN1>longbN2){
    longAdd = longbN1;
  }else{
    longAdd = longbN2;
  }
  int overflow=0;
  if (longAdd>=TAILLEMAX){
    overflow=1;
  }
  for (int i = 0;i<longAdd+1;i++){
    int r;
    if (retenue) {
      r=1+bN1[i]+bN2[i];
    }else{
      r=bN1[i]+bN2[i];
    }
    retenue=false;
    if (r>9){
      retenue=true;
      //allocation et mise à 0
      bigInt rBigInt=initBigInt();
      //on transforme un int en bigInt.rBigInt stocke donc, une fois la méthode faite, r
      intToBigInt(r,rBigInt);
      res[i]=rBigInt[0];
      freeBigInt(rBigInt);
    }else{
      res[i]=r;
    }
  }
  return overflow;
}





/*!
************************************************
* \brief Multiplie deux Grand Entiers avec l'algorithme suivant:
* stocker les 10 valeurs j*bN2 pour 1<=j<=9
* Pour chaque chiffre j=bN1[i] de bN1, partant de i=0,
* multiplier  j*bN2 par 10^i et l'ajouter au resultat
* \param  bN1 Grand Entier
* \param  bN2 Grand Entier
* \param  res le grand entier bN1*bN2
* \result Un entier: 1 en cas d'overflos, O sinon
* \warning res doit être déjà alloué,
* ************************************************/
int mulBigInt(bigInt bN1,bigInt bN2,bigInt res)
{
  bigInt bNTemp;
  for (int i=0;i<getNbChiffreBigInt(bN1);i++){
    bNTemp=initBigInt();
    fot (int j=0;j<)
  }
  return 0;
 }

