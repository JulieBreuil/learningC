#include <stdio.h>
#include <stdlib.h>

#include "type_bigInt.h"
#include "util_bigInt.h"
#include "io_bigInt.h"
#include "bigInt.h"
#include "testBigInt.h"

void  errorT(const char *mess)
{
  fprintf(stdout,"Error in testing: %s\n",mess);
  exit(-1);
}


void testBinopFile(char *file,int (*func)(bigInt,bigInt,bigInt))
{
  FILE *fich;
  bigInt bN1,bN2,bN3,res;
  int finit=FALSE,chiffre;

  fich=fopen(file,"r");
  if (fich==NULL) errorT("testOnFile: test file not found");

  while (!finit)
    {
      bN1=initBigInt();
      bN2=initBigInt();
      bN3=initBigInt();
      res=initBigInt();
      chiffre=readBigInt(fich,bN1);
      chiffre=readBigInt(fich,bN2);
      chiffre=readBigInt(fich,res);

      func(bN1,bN2,bN3);
      
      if (!(bigIntEqualQ(bN3,res))) 
	{
	  fprintf(stdout,"result found: ");
	  printBigInt(bN3);
	  fprintf(stdout,"\nshould be:");
	  printBigInt(res);
	  errorT("Erreur testAddOnFile \n");
	  
	}
      else
	{
	  fprintf(stdout,".");
	}
      if (chiffre==EOF)
	finit=TRUE;

      freeBigInt(bN1);
      freeBigInt(bN2);
      freeBigInt(bN3);
      freeBigInt(res);

    }


  fprintf(stdout,"passed!\n");
  fclose(fich);
}



