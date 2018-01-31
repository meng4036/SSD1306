/*
 * ssd1306.h
 *
 *  Created on: 2018��1��24��
 *      Author: meng4
 */

#ifndef SSD1306_H_
#define SSD1306_H_

#include <stdint.h>
#include <stdbool.h>

#define HORIZONTAL_MODE		0
#define VERTICAL_MODE		1
#define PAGE_MODE			2

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

void oled_scroll_active();
void oled_scroll_deactive();
void oled_scroll_right(uint8_t start, uint8_t stop);
void oled_scroll_left(uint8_t start, uint8_t stop);
void oled_vertial_scroll_range(uint8_t start, uint8_t stop);
void oled_scroll_up(uint8_t start, uint8_t stop, uint8_t speed);
void oled_scroll_down(uint8_t start, uint8_t stop, uint8_t speed);

void oled_write_data(const uint8_t *data, uint8_t size);

void oled_write_byte(uint8_t data);
#endif /* SSD1306_H_ */
