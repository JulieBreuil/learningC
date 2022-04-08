#include <stdio.h>
#include <stdlib.h>

#include "type_bigInt.h"
#include "util_bigInt.h"
#include "io_bigInt.h"
#include "bigInt.h"

int main()
{
  bigInt bN1, bN2,bN,bNT,res;

  bN1=initBigInt();
  bN2=initBigInt();
  bN=initBigInt();
  bNT=initBigInt();
  res=initBigInt();

  fprintf(stdout,"Developping big Int library\n");
  intToBigInt(56,bN1);
  intToBigInt(2,bN2);
  fprintf(stdout,"Test de la fonction times10BigInt\n");
  times10BigInt(bN1,bNT);
  printBigInt(bNT);
  fprintf(stdout,"Test de la fonction mulBigInt\n");
  mulBigInt(bN1,bN2,res);
  printBigInt(res);

  addBigInt(bN1,bN2,bN);

  if (bigIntToInt(bN)!= 10) 
    printf("\nError addBigInt is not correct: %d + %d != %d\n",
	   bigIntToInt(bN1),bigIntToInt(bN2),bigIntToInt(bN));
  

  fprintf(stdout,"Testing Factorielle\n");
  zeroBigInt(bN1);
  zeroBigInt(bN2);
  intToBigInt(10,bN1);
  //  factorielleBigInt(bN1,bN2);
  printBigInt(bN2);

  freeBigInt(bN1);
  freeBigInt(bN2);
  freeBigInt(bN);
    
  return(0);
}
