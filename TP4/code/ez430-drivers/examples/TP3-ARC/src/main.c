/**
 *  \file   main.c
 *  \brief  eZ430-RF2500 CRO example 1
 *  \author Tanguy Risset, Guillaume Salagnac
 *  \date   2017
 **/

#include <msp430x22x4.h>
#include <msp430.h>
#if defined(__GNUC__) && defined(__MSP430__)
/* This is the MSPGCC compiler */
#include <iomacros.h>
#include <legacymsp430.h>
#elif defined(__IAR_SYSTEMS_ICC__)
/* This is the IAR compiler */
//#include <io430.h>
#endif

#include <stdio.h>
#include "watchdog.h"

#define ID 1

int main(void)
{
  watchdog_stop();
  
  // select GPIO mode
  P1SEL = 0;
  // set P1.1 to output direction
  P1DIR = 1;
  for(;;)
    {
      int i;
      // software delay
      for(i=0;i<20000;i++)
	{}//do nothing
      // turn red LED on
      P1OUT = 1;
      for(i=0;i<20000;i++)
	{}//do nothing
      // turn red LED off
      P1OUT = 0;
    }
}
