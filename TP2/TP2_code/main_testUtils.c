#include <stdio.h>
#include <stdlib.h>

#include "type_bigInt.h"
#include "util_bigInt.h"
#include "io_bigInt.h"
#include "bigInt.h"
#include "testUtils.h"

int main()
{int res;

  res=test_initBigInt();
  if (res == 0)   res=test_intToBigInt();
  if (res == 0)   res=test_stringToBigInt();
  if (res == 0)   res=test_sprintBigInt();
  if (res == 0)   res=test_getNbChiffreInt();
  if (res == 0)   res=test_getNbChiffreBigInt();
  


  if (res==0) 
    fprintf(stdout,"All test passed...\n");
  else
    fprintf(stdout,"Some test failed...\n");
    
		
  return 0;
 
}
