#include <stdio.h>
#include <stdlib.h>

#include "type_bigInt.h"
#include "util_bigInt.h"
#include "io_bigInt.h"
#include "bigInt.h"

void  errorT(const char *mess)
{
  fprintf(stdout,"Error in testing: %s\n",mess);
  exit(-1);
}


void setVeryBigBigInt(bigInt bN)
{
  zeroBigInt(bN);
  bN[TAILLEMAX-1]=9;
}

int test_initBigInt()
{
  bigInt bN;
  int i;
  
  fprintf(stderr,"Testing initBigInt\n");
  bN=initBigInt();
  for (i=0; i<TAILLEMAX;i++)
    {
      if (bN[i]!=0)  errorT("initBigInt");
    }

  freeBigInt(bN);

  return 0; 
}


int test_getNbChiffreInt()
{
  
  fprintf(stderr,"Testing getNbChiffreInt\n");
  if (getNbChiffreInt(0)!= 0)  errorT("getNbChiffreInt(0)");
  if (getNbChiffreInt(1) != 1)  errorT("getNbChiffreInt(1)");
  if (getNbChiffreInt(9) != 1)   errorT("getNbChiffreInt(9)");
  if (getNbChiffreInt(10) != 2)   errorT("getNbChiffreInt(10)");
  if (getNbChiffreInt(10001) != 5)   errorT("getNbChiffreInt(10001)");
  
  return(0);
}

int test_getNbChiffreBigInt()
{
  bigInt bN,bN2;
  
  bN=initBigInt();
  bN2=initBigInt();
  fprintf(stderr,"Testing getNbChiffreBigInt\n");
  intToBigInt(0,bN2);
  if (getNbChiffreBigInt(bN2)!= 0)  errorT("getNbChiffreBigInt(0)");
  intToBigInt(1,bN2);
  if (getNbChiffreBigInt(bN2) != 1)   errorT("getNbChiffreBigInt(1)");
  intToBigInt(9,bN2);
  if (getNbChiffreBigInt(bN2) != 1)   errorT("getNbChiffreBigInt(9)");
  intToBigInt(10,bN2);
  if (getNbChiffreBigInt(bN2) != 2)   errorT("getNbChiffreBigInt(10)");
  intToBigInt(10001,bN2);
  if (getNbChiffreBigInt(bN2) != 5)   errorT("getNbChiffreBigInt(10001");
  setVeryBigBigInt(bN);
  if (getNbChiffreBigInt(bN) != TAILLEMAX)   errorT("getNbChiffreBigInt(TAILLEMAX)");
  
  freeBigInt(bN);
  freeBigInt(bN2);

  return(0);
}

int test_intToBigInt()
{
  bigInt n1;

  fprintf(stderr,"Testing intToBigInt\n");
  n1=initBigInt();

  intToBigInt(9086,n1);
  
  if ((n1[3]!=9)||(n1[2]!=0)||(n1[1]!=8)||(n1[0]!=6))
    {
       errorT("intToBigInt");
    }

  freeBigInt(n1);
  return(0);
}


int test_stringToBigInt()
{
  bigInt n1;

  fprintf(stderr,"Testing stringToBigInt\n");
  n1=initBigInt();

  stringToBigInt("9086",n1);

  if ((n1[3]!=9)||(n1[2]!=0)||(n1[1]!=8)||(n1[0]!=6))
    {
       errorT("stringToBigInt");
    }


  freeBigInt(n1);
  return(0);
}



int test_sprintBigInt()
{
  bigInt n1;
  char *n1_s;

  fprintf(stderr,"Testing sprintBigInt\n");
  n1=initBigInt();

  intToBigInt(9086,n1);
  n1_s=sprintBigInt(n1);
  

  if ((n1_s[0]!='9')||(n1_s[1]!='0')||(n1_s[2]!='8')||(n1_s[3]!='6'))
    {
       errorT("sprintBigInt");
    }


  freeBigInt(n1);
  free(n1_s);
  return(0);
}




