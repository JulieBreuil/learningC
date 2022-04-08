#ifndef UTIL_BIGINT_H
#define UTIL_BIGINT_H

void error(const char *mess);
bigInt initBigInt();
void zeroBigInt(bigInt bN);
void freeBigInt(bigInt bN);
int getNbChiffreInt(int N);
int getNbChiffreBigInt(bigInt bN);
void printBigInt(bigInt bN);
char *sprintBigInt(bigInt bN);
void copyBigInt(bigInt src,bigInt dst);
int bigIntEqualQ(bigInt bN1,bigInt bN2);
void  intToBigInt(int N,bigInt bN);
void  stringToBigInt(char *N_s,bigInt bN);
int bigIntToInt(bigInt nN);

#endif
