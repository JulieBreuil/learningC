#include <stdio.h>
#include <stdlib.h>

#include "type_bigInt.h"
#include "util_bigInt.h"
#include "io_bigInt.h"
#include "bigInt.h"

int main()
{
  bigInt bN1, bN2,bN;

  bN1=initBigInt();
  bN2=initBigInt();
  bN=initBigInt();
  

  fprintf(stdout,"Developping big Int library\n");
  intToBigInt(1,bN1);
  intToBigInt(9,bN2);
  addBigInt(bN1,bN2,bN);

  if (bigIntToInt(bN)!= 10) 
    printf("Error addBigInt is not correct: %d + %d != %d\n",
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
