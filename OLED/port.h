/*
 * port.h
 *
 *  Created on: 2018��1��24��
 *      Author: meng4
 */

#ifndef PORT_H_
#define PORT_H_

#include <msp430.h>

void port_msp430_init();

void ssd1306_init();
void ssd1306_write_byte(uint8_t byte);

void ssd1306_enable_data();
void ssd1306_enable_command();
void ssd1306_chip_select();
void ssd1306_chip_deselect();


#endif /* PORT_H_ */
