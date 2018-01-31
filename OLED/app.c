/*
 * app.c
 *
 *  Created on: 2018��1��30��
 *      Author: meng4
 */
#include "font6x8.h"
#include "ssd1306.h"
#include "app.h"

void oled_clear_screen() {
	uint8_t i,j;
	for(i=0; i<8; i++) {
		oled_set_page_address(i);
		oled_set_column_address(0x00);
		for (j=128; j!=0; j--) {
			oled_write_byte(0x00);
		}
	}
}

void oled_set_position(uint8_t x, uint8_t y) {
	oled_set_page_address(x);
	oled_set_column_address(y);
}

void oled_show_char(char chr) {

	uint16_t column = (chr - ' ') * 6;
	oled_write_data(font6x8 + column, 6);
}

void oled_show_string(const char *str) {
	const char *pstr = str;
    int len = 0;
    while (*str ++ != '\0')
        ++ len;

    int i = 0;
    for (i=0; i<len; i++) {
    	char c = pstr[i];
    	oled_show_char(c);
    }
}
