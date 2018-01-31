/*
 * app.h
 *
 *  Created on: 2018��1��30��
 *      Author: meng4
 */

#ifndef APP_H_
#define APP_H_

#include <stdint.h>

void oled_set_position(uint8_t x, uint8_t y);

void oled_clear_screen();

void oled_show_char(char chr);

void oled_show_string(const char *str);


#endif /* APP_H_ */
