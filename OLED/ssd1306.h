/*
 * ssd1306.h
 *
 *  Created on: 2018Äê1ÔÂ24ÈÕ
 *      Author: meng4
 */

#ifndef SSD1306_H_
#define SSD1306_H_

#include <stdint.h>
#include <stdbool.h>


void display_init();
void oled_init();

void oled_display_off();
void oled_display_on();

void oled_set_display_mode(bool is_normal);
void oled_set_display_offset(uint8_t offset);
void oled_set_display_start_line(uint8_t line);
void oled_set_multiplex_ratio(uint8_t ratio);

void oled_enable_charge_pump();
void oled_set_normal_display();

void oled_set_memory_mode(uint8_t mode);

void oled_set_column_address(uint8_t column);
void oled_set_page_address(uint8_t page);

#endif /* SSD1306_H_ */
