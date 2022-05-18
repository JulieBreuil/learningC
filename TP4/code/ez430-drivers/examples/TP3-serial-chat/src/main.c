/**
 *  \file   main.c
 *  \brief  eZ430-RF2500 tutorial, serial for CRO
 *  \author Antoine Fraboulet, Tanguy Risset
 *  \date   2010
 **/

#include <msp430x22x4.h>

#if defined(__GNUC__) && defined(__MSP430__)
/* This is the MSPGCC compiler */
#include <msp430.h>
#include <iomacros.h>
#include <legacymsp430.h>
#elif defined(__IAR_SYSTEMS_ICC__)
/* This is the IAR compiler */
//#include <io430.h>
#endif

#include <stdio.h>
#include <string.h>

#include "leds.h"
#include "clock.h"
#include "watchdog.h"
#include "uart.h"
#include "spi.h"
#include "cc2500.h"
#include "lpm_compat.h"

#define ID 1

/* ************************************************** */
/* ************************************************** */
/* ************************************************** */

#define SERIAL_BUFFER_SIZE 32

/* serial_buffer used for keyboard buffering */
static char serial_buffer[SERIAL_BUFFER_SIZE];
static uint8_t radio_rx_buffer[SERIAL_BUFFER_SIZE];
static uint8_t radio_tx_buffer[SERIAL_BUFFER_SIZE];
volatile uint8_t serial_wptr;
volatile uint8_t serial_size;
volatile uint8_t msg_size; /* can be different from serial size */


void serial_init()
{
  int i;
  
  for(i=0;i<SERIAL_BUFFER_SIZE;i++)
    serial_buffer[i]=0;
  serial_wptr = 0;
  serial_size = 0;
  msg_size = 0;
}

/* ************************************************** */


static void printhex(char *buffer, unsigned int len)
{
    unsigned int i;
    for(i = 0; i < len; i++)
    {
      printf("%02X ", buffer[i]);
    }
}

/*************************************************** */
/* received message decoding and printing            */
/*****************************************************/
void decode_message(uint8_t *buffer, int size)
{
  /********** Your decoding methode goes here *************/
  printf("message received:");
  printhex((char *)buffer, size);
  putchar('\r');
  putchar('\n');
}
  
/* ************************************************** */
/* Call back called when a packet is received         */
/* ************************************************** */

void radio_cb(uint8_t *buffer, int size, int8_t rssi)
{
  led_green_switch();
  switch (size)
    {
    case 0:
      printf("msg size 0\r\n");
      break;
    case -EEMPTY:
      printf("msg emptyr\r\n");
      break;
    case -ERXFLOW:
      printf("msg rx overflow\r\n");
      break;
    case -ERXBADCRC:
      printf("msg rx bad CRC\r\n");
      break;
    case -ETXFLOW:
      printf("msg tx overflow\r\n");
      break;
    default:
      if (size > 0)
	{
	  decode_message(buffer,size);
	}
      break;
    }
  
  cc2500_rx_enter();
}

/*************************************************** */
/* sent message coding printing                     */
/*****************************************************/

void encode_message(char *in_buffer,uint8_t *out_buffer, int size)
{
  /********** Your coding methode goes here *************/
  memcpy(out_buffer, in_buffer, SERIAL_BUFFER_SIZE);
  msg_size=serial_size;
}

static void radio_send_message()
{
  cc2500_utx((const char *)serial_buffer, msg_size);
  printf("sent: ");
  printhex(serial_buffer, msg_size);
  putchar('\r');
  putchar('\n');
  cc2500_rx_enter();
}


/* ************************************************** */
/* Send the content of the serial_buffer              */
/* and re-initialize the serial_buffer                */
/* ************************************************** */
void serial_send()
{
  dint();
  if (serial_size > 0)
    {
      encode_message(serial_buffer,radio_tx_buffer,serial_size);
      radio_send_message();
      serial_init();
    }
  eint();
  led_red_switch();
}


/* ************************************************** */
/* bottom half of serial call back:                   */
/* treatement of char typed on keyboard               */
/* ************************************************** */
void serial_put(uint8_t data)
{
  serial_buffer[serial_wptr] = data;
  serial_wptr = (serial_wptr + 1) % SERIAL_BUFFER_SIZE;
  if (serial_size < SERIAL_BUFFER_SIZE-1)
    {
      serial_size ++;
    }
  else
    {
      /*  we get a serial_overflow  */
      serial_init();
    }
  if (data=='\r')
    {
      serial_send();
    }
      
}


/* ************************************************** */
/* serial callback: uart received chat from keyboard  */
/* ************************************************** */

int serial_cb(unsigned char data)
{
  serial_put(data);
  putchar(data); /* echo */
  return 1; /* will wakeup from LPMx */
}

/* ************************************************** */
/* CRO serial radio application                       */
/* each pacquet received is analyzed                  */
/* each line entered  on serial portis send           */
/* serial lines should be less than 32 char           */
/******************************************************/
int main(void)
{
  watchdog_stop();
  
  set_mcu_speed_dco_mclk_16MHz_smclk_8MHz();

  leds_init();
  
  led_red_on();
  
  uart_init(UART_9600_SMCLK_8MHZ);
  serial_init();
  uart_register_cb(serial_cb);
  spi_init();
  cc2500_init();
  cc2500_rx_register_buffer(radio_rx_buffer, SERIAL_BUFFER_SIZE);
  cc2500_rx_register_cb(radio_cb);
  cc2500_rx_enter();
  
  printf("\rserial test application: CRO serial\n\r");
  eint();
  
  for(;;)
    {
      LPM(1);
    }
}

/* ************************************************** */
/* ************************************************** */
