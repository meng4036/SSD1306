/*
 * port.c
 *
 *  Created on: 2018��1��24��
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


void port_msp430_init() {
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

void ssd1306_init() {
	const uint8_t cmds[] = {
			0xAE,
			0x00,
			0x10,

			0x40,

			0x81,
			0x80,

			0xA1,
			0xC8,
			0xA6,
			0xA8,
			0x3F,
			0xD3,
			0x00,
			0xD5,
			0x80,
			0xD9,
			0xF1,
			0xDA,
			0x12,
			0xDB,
			0x40,

			0x20,
			0x00,

			0x8D,
			0x14,
			0xA4,
			0xA6,
			0xAF,
	};
	ssd1306_chip_select();
	ssd1306_enable_command();
	int i = 0;
	for (i=0; i<sizeof(cmds); i++) {
		ssd1306_write_byte(cmds[i]);
	}
    ssd1306_chip_deselect();
}

void ssd1306_write_byte( uint8_t byte) {
	UCB0TXBUF = byte;
	while (UCB0STAT & UCBUSY);
	(void)UCB0RXBUF;
}

void ssd1306_enable_command() {
	P1OUT &= ~OLED_DC;
}

void ssd1306_enable_data() {
	P1OUT |= OLED_DC;
}

void ssd1306_chip_select() {
  P1OUT &= ~OLED_CS;
}

void ssd1306_chip_deselect() {
  P1OUT |= OLED_CS;
}
