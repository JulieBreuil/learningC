/**
 *  \file   main.c
 *  \brief  eZ430-RF2500 tutorial, serial for CRO
 *  \author Antoine Fraboulet, Tanguy Risset
 *  \date   2010
 **/

#include <msp430x22x4.h>

#include <msp430.h>
#include <iomacros.h>
#include <legacymsp430.h>

#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "leds.h"
#include "clock.h"
#include "timer.h"
#include "watchdog.h"
#include "uart.h"
#include "spi.h"
#include "cc2500.h"
#include "lpm_compat.h"

#include "pt.h"

/* ************************************************** */
/* TODO: modify your own ID                           */
#define ID 21
/* ************************************************** */

/* use 1 timer for periodic radio send                */
/* 100 Hz timer A                                     */
#define TIMER_PERIOD_MS 10
#define NUM_TIMERS 1
static uint16_t timer[NUM_TIMERS];
#define TIMER_RADIO_SEND timer[0]         


static int DEBUG=1;
  
/*********************************************************/
/* Packet structure:                                     */
/* ----------------------------------------------------- */
/* | ID | coding_state | message(<=28bytes) | RSSI| LQI| */
/* ----------------------------------------------------- */
/*   0         1        2                        31      */
/*********************************************************/

#define PKTLEN 32
#define MSG_BYTE_NODE_ID 0U
#define CODING_BYTE 1U

/* serial_buffer used to code or decode message  */
static uint8_t radio_rx_buffer[PKTLEN];
static uint8_t radio_tx_buffer[PKTLEN];

/* buffer init functions                         */
void buffer_init(uint8_t *buffer,int size)
{
  int i;
  for (i=0; i<size;i++)
    buffer[i]=0;
}

/* *****************************************************/
/*  Sotware Timer functions: counting timer interrupts */
/* *****************************************************/

void timer_tick_cb() {
    int i;
    for(i = 0; i < NUM_TIMERS; i++)
    {
        if(timer[i] != UINT_MAX) {
            timer[i]++;
        }
    }
}

int timer_reached(uint16_t timer, uint16_t count) {
    return (timer >= count);
}

/* ************************************************** */
/* packet printing functions                          */
/* ************************************************** */

static void printhex(uint8_t *buffer, unsigned int len)
{
    unsigned int i;
    for(i = 0; i < len; i++)
    {
      printf("%02X ", buffer[i]);
    }
}

static void dump_message(uint8_t *buffer,int size)
{
  if (buffer[MSG_BYTE_NODE_ID]==0x0F){
    printf("message received\r\n  content: ");
    printhex(buffer, PKTLEN);
    printf("\r\n  from node: 0x%02X, coding_state: %d\r\n",
      buffer[MSG_BYTE_NODE_ID],buffer[CODING_BYTE] );
  }
}


/* ************************************************** */
/* decoding functions                                 */
/* TODO: decode successive coding states              */
/* ************************************************** */
void decode_message(uint8_t *buffer, int size)
{
  int i;
  static uint8_t decoded_message[PKTLEN];

  int state_coding = buffer[1];
  /********** Your decoding methode goes here *************/
  switch (state_coding) {
  case 0:
    {
      memcpy(decoded_message,buffer,size);
      break;
    }
  case 1:
    {
      for (i=2; i<size-2; i++){
        buffer[i]=buffer[i]^(0xD5);
      }
      memcpy(decoded_message,buffer,size);
      break;
    }
  case 2:
    {
      for (i=2;i<size-2;i=i+4){
        buffer[i]= buffer[i]^(0xAA);
        buffer[i+1]= buffer[i+1]^(0xD5);
        buffer[i+2]= buffer[i+2]^(0x61);
        buffer[i+3]= buffer[i+3]^(0xCF);
      }
      //copie le contenu de buffer (message non décodé mais qu'on vient de décoder) dans decoded_message (message décod")
      memcpy(decoded_message,buffer,size);
      break;
    }
  case 3:
    {
      for (i=2; i<size-2; i++){
        buffer[i]=buffer[i]^(0xD4);
      }
      memcpy(decoded_message,buffer,size);
      break;
    }
  default:
    break;
  }
  
  if (DEBUG && buffer[MSG_BYTE_NODE_ID]==0x0F)
    {
      printf("  decoded message:  ");
      for (i=2;i<size-2;i++)
	putchar(decoded_message[i]);
      putchar('\r');
      putchar('\n');
    }
}
  
/* ************************************************** */
/* radio Call back: called when a packet is received         */
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
	{ /* handling message */
	  if (DEBUG)
	    dump_message(buffer,size);
	  decode_message(buffer,size);
	}
      break;
    }
  
  buffer_init(radio_rx_buffer,PKTLEN);
  cc2500_rx_enter();
}

/*************************************************** */
/* encoding message and printing                     */
/* TODO: once key 3 is known, encode "hello" message */
/*****************************************************/

int encode_message(uint8_t *in_buffer,uint8_t *out_buffer, int size)
{

  /********** change your encode state here  *************/
  int state_coding = 3; 

  /********** Your coding methode goes here *************/
  /* add ID as first byte, and state_coding as byte 2   */
  out_buffer[MSG_BYTE_NODE_ID]=ID;
  out_buffer[CODING_BYTE]=state_coding;
  int i;
  switch (state_coding) {
  case 0:
    {
      memcpy(out_buffer+2,in_buffer,size);
      break;
    }
  case 1:
    {
      /* to be modified */
      memcpy(out_buffer+2,in_buffer,size);
    }
  case 2:
    {
     /* to be modified */
      memcpy(out_buffer+2,in_buffer,size);
      break;
    }
  case 3:
    {
      //memcpy(out_buffer+2,in_buffer,size);
      for (i=2; i<size-2; i++){
        out_buffer[i]=in_buffer[i-2]^(0xD4);
      }
      
      break;
    }
  default:
    break;
  }

  return(size+2);
}

static void radio_send_message()
{
  int size;

  /* constant message */
  uint8_t message[PKTLEN-1];
  int msg_size=30;

  buffer_init(message,PKTLEN-1);
  sprintf((char *)message,"hello from ID: Ox%X",ID);
  size=encode_message(message,radio_tx_buffer,msg_size);
  
  cc2500_utx((const char *)radio_tx_buffer,size);
  printf("sent:     ");
  printhex(radio_tx_buffer, size);
  putchar('\r');
  putchar('\n');
  printf("in ascii: ");
  printf("%s",message);
  putchar('\r');
  putchar('\n');

  buffer_init(radio_tx_buffer,PKTLEN);
  cc2500_rx_enter();
}




/* ************************************************** */
/*  send periodicaly the encoded      */
/* every 10s                                          */
/* ************************************************** */
periodic_send()
{
  while (1)
    {
      TIMER_RADIO_SEND = 0;
      while(!timer_reached(TIMER_RADIO_SEND, 1000))
	{
	  nop();
	}
      radio_send_message();
    }

}



/* ***************************************************** */
/* serial echo: uart received char from keyboard         */
/* unused unless you want to desactivate the DEBUG mode  */
/* *******************************************************/

int serial_cb(unsigned char data)
{
  putchar(data); /* echo */
  //if (data=='d')  DEBUG=!DEBUG;
  return 1; /* will wakeup from LPMx */
}

/* *******************************************************/
/* main()                                                */
/* CRO TC-MSP challenge: student/client code             */
/* each packet received is analyzed and printed          */
/* every 10 second, an encoded packet is sent            */
/* encoding should follow labs instructions              */
/* messages should be less than 32 char                  */
/* Packet structure:                                     */
/* ----------------------------------------------------- */
/* | ID | coding_state | message(<=28bytes) | RSSI| LQI| */
/* ----------------------------------------------------- */
/*   0         1        2                        31      */
/********************************************************/
int main(void)
{
  //arrêt watchdag horloge
  watchdog_stop();
  
  set_mcu_speed_dco_mclk_16MHz_smclk_8MHz();

  leds_init();
  led_red_on();

  
  /* timer init: an interrupt every TIMER_PERIOD_MS ms */
  timerA_init();
  timerA_register_cb(&timer_tick_cb);
  timerA_start_milliseconds(TIMER_PERIOD_MS);
  
  /* uart init: echo uart, useless here */
  uart_init(UART_9600_SMCLK_8MHZ);
  uart_register_cb(serial_cb);

  /* spi and radio init for radio packet reception */
  spi_init();
  cc2500_init();
  cc2500_rx_register_buffer(radio_rx_buffer, PKTLEN);
  cc2500_rx_register_cb(radio_cb);
  cc2500_rx_enter();
  
  printf("\rserial test application: STUDENT INIT\n\r");

  /* enable interrupts */
  eint();

  /* periodic send of packet  */
    periodic_send();
}

/* ************************************************** */
/* ************************************************** */
