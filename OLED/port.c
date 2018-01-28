/*
 * port.c
 *
 *  Created on: 2018Äê1ÔÂ24ÈÕ
 *      Author: meng4
 */
#include <stdint.h>
#include <msp430.h>
#include "port.h"

#define MHZ               1

#define OLED_SCLK         BIT5
#define OLED_SDIN         BIT7
#define OLED_RES          BIT2
#define OLED_DC           BIT3
#define OLED_CS           BIT4
// this is fake output, not connected
#define OLED_SDOUT        BIT6
#define OLED_CONTRAST     0x80
#define OLEDS             (OLED_RES | OLED_DC | OLED_CS)

void port_initialize() {
  unsigned char commands[] = {

    //0xd5,//--set display clock divide ratio/oscillator frequency
    //0x80,//--set divide ratio

    //0xa8,//--set multiplex ratio(1 to 64)
    //0x1f,//--1/32 duty

    //0xd3,//-set display offset
    //0x00,//-not offset

    //0x8d,//--set Charge Pump enable/disable
    //0x14,//--set(0x10) disable

    //0x40,//--set start line address

    //0xa6,//--set normal display

    //0xa4,//Disable Entire Display On

    0xa1,//--set segment re-map 128 to 0

    0xC8,//--Set COM Output Scan Direction 64 to 0

    0xda,//--set com pins hardware configuration
    0x42,

    0x81,//--set contrast control register
    OLED_CONTRAST,

    0xd9,//--set pre-charge period
    0xf1,

    0xdb,//--set vcomh
    0x40,

    0xaf//--turn on oled panel
  };
  ssd1306_chip_select();
  int i = 0;
  for (i=0; i<sizeof(commands); i++) {
	  ssd1306_write_byte(commands[i]);
  }
  ssd1306_chip_deselect();
}

void ssd1306_init() {
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT
	BCSCTL1 = CALBC1_1MHZ; // Set DCO
	DCOCTL = CALDCO_1MHZ;

	P1DIR |= (OLEDS | BIT0 | OLED_SCLK);
	P1OUT &= ~(OLEDS | BIT0);

	//USCI setup
	UCB0CTL1 = UCSWRST | UCSSEL_2; // stop USCI and choose SCLK as source
	UCB0CTL0 = UCCKPH | UCMODE_0 | UCMSB | UCSYNC | UCMST; // logic triggered before rising clock, msb, spi, master
	UCB0BR0 |= 1; // send bit on every clock tick
	UCB0BR1 = 0;
	P1SEL |= OLED_SCLK | OLED_SDIN | OLED_SDOUT; // enalbe USCI functions on ports
	P1SEL2 |= OLED_SCLK | OLED_SDIN | OLED_SDOUT; // missing this on launchpad will make code not working
	UCB0CTL1 &= ~UCSWRST; // start USCI

	P1OUT |= OLED_RES;
	__delay_cycles(20 * MHZ);
	P1OUT &= ~OLED_RES;
	__delay_cycles(200 * MHZ);
	P1OUT |= OLED_RES;
	__delay_cycles(200 * MHZ);
}

void ssd1306_write_byte( uint8_t byte) {
	UCB0TXBUF = byte;
	while (UCB0STAT & UCBUSY);
	(void)UCB0RXBUF;
}

inline void ssd1306_enable_command() {
	P1OUT &= ~OLED_DC;
}

inline void ssd1306_enable_data() {
	P1OUT |= OLED_DC;
}

void ssd1306_chip_select() {
  P1OUT &= ~OLED_CS;
}

void ssd1306_chip_deselect() {
  P1OUT |= OLED_CS;
}
