#include <stdio.h>
#include <stdlib.h>

#include "type_bigInt.h"
#include "util_bigInt.h"
#include "io_bigInt.h"
#include "bigInt.h"
#include "testBigInt.h"

int main()
{


  fprintf(stdout,"Testing AddBigInt:\n");
  testBinopFile("dataTestAdd.txt",addBigInt);
  fprintf(stdout,"Testing MulBigInt:\n");
  testBinopFile("dataTestMul.txt",mulBigInt);
  

  return(0);
}
