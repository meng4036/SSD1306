/*
 * ssd1306.c
 *
 *  Created on: 2018年1月24日
 *      Author: meng4
 */
#include <stdint.h>
#include "ssd1306.h"
#include "port.h"

void oled_init() {
	port_msp430_init();
	ssd1306_init();
}

void oled_set_page_address(uint8_t page) {
	ssd1306_chip_select();
	ssd1306_enable_command();
    ssd1306_write_byte(0xb0 | page);
    ssd1306_chip_deselect();
}

void oled_set_column_address(uint8_t column) {
	ssd1306_chip_select();
	ssd1306_enable_command();
	ssd1306_write_byte(0x10 | (column >> 4));
	ssd1306_write_byte(0x0f & column);
    ssd1306_chip_deselect();
}

void oled_set_memory_mode(uint8_t mode) {
	ssd1306_chip_select();
	ssd1306_enable_command();
	ssd1306_write_byte(0x03 & mode);
	ssd1306_chip_deselect();
}

void oled_set_multiplex_ratio(uint8_t ratio) {
	ssd1306_chip_select();
	ssd1306_enable_command();
	ssd1306_write_byte(0xa8);
	ssd1306_write_byte(ratio);
	ssd1306_chip_deselect();
}

void oled_set_segment_map(uint8_t map) {
	ssd1306_chip_select();
	ssd1306_enable_command();
	if (map & 0x01) {
		ssd1306_write_byte(0xa1);
	} else {
		ssd1306_write_byte(0xa0);
	}
	ssd1306_chip_deselect();
}

/**
 *	Set Display Start Line register to determine starting address of display RAM
 *	by selecting a value from 0 to 63
 *	@param line - RAM row number to map to COM0
 */
void oled_set_display_start_line(uint8_t line) {
	ssd1306_chip_select();
	ssd1306_enable_command();
	ssd1306_write_byte(line);
	ssd1306_chip_deselect();
}

/**
 * set display offset
 * @param offset
 * 	specifies the mapping of the display start line to one of COM0~COM63
 */
void oled_set_display_offset(uint8_t offset) {
	ssd1306_chip_select();
	ssd1306_enable_command();
	ssd1306_write_byte(0xd3);
	ssd1306_write_byte(offset);
	ssd1306_chip_deselect();
}

void oled_enable_charge_pump() {
	ssd1306_chip_select();
	ssd1306_enable_command();
	ssd1306_write_byte(0x8d);
	ssd1306_write_byte(0x14);
	ssd1306_chip_deselect();
}

void oled_disable_chare_pump() {
	ssd1306_chip_select();
	ssd1306_enable_command();
	ssd1306_write_byte(0x8d);
	ssd1306_write_byte(0x10);
	ssd1306_chip_deselect();
}

void oled_set_normal_display() {
	ssd1306_chip_select();
	ssd1306_enable_command();
	ssd1306_write_byte(0xa6);
	ssd1306_chip_deselect();
}

void oled_set_inverse_display() {
	ssd1306_chip_select();
	ssd1306_enable_command();
	ssd1306_write_byte(0xa7);
	ssd1306_chip_deselect();
}


void oled_display_off() {
	ssd1306_chip_select();
	ssd1306_enable_command();
	ssd1306_write_byte(0xae);
	ssd1306_chip_deselect();
}

void oled_display_on() {
	ssd1306_chip_select();
	ssd1306_enable_command();
	ssd1306_write_byte(0xaf);
	ssd1306_chip_deselect();
}

static void oled_write_cmd(const char* cmd, uint8_t size) {
	uint8_t i;
	ssd1306_chip_select();
	ssd1306_enable_command();
	for (i=0; i<size; i++) {
		ssd1306_write_byte(cmd[i]);
	}
	ssd1306_chip_deselect();
}

void oled_scroll_active() {
	ssd1306_chip_select();
	ssd1306_enable_command();
	ssd1306_write_byte(0x2f);
	ssd1306_chip_deselect();
}

void oled_scroll_deactive() {
	ssd1306_chip_select();
	ssd1306_enable_command();
	ssd1306_write_byte(0x2e);
	ssd1306_chip_deselect();
}

void oled_scroll_right(uint8_t start, uint8_t end) {
	ssd1306_chip_select();
	ssd1306_enable_command();
	ssd1306_write_byte(0x26);
	ssd1306_write_byte(0x00);
	ssd1306_write_byte(start);
	ssd1306_write_byte(0x08);
	ssd1306_write_byte(end);
	ssd1306_write_byte(0x00);
	ssd1306_write_byte(0xff);
	ssd1306_write_byte(0x2f);
	ssd1306_chip_deselect();
}

void oled_scroll_left(uint8_t start, uint8_t stop) {
	ssd1306_chip_select();
	ssd1306_enable_command();
	ssd1306_write_byte(0x2e);
	ssd1306_write_byte(0x27);
	ssd1306_write_byte(0x00);
	ssd1306_write_byte(start);
	ssd1306_write_byte(0x00);
	ssd1306_write_byte(stop);
	ssd1306_write_byte(0x00);
	ssd1306_write_byte(0xff);
	ssd1306_write_byte(0x2f);
	ssd1306_chip_deselect();
}


void oled_vertial_scroll_range(uint8_t start, uint8_t stop) {
	ssd1306_chip_select();
	ssd1306_enable_command();
	ssd1306_write_byte(0xa3);
	ssd1306_write_byte(start);
	ssd1306_write_byte(stop);
}

void oled_scroll_up(uint8_t start, uint8_t end, uint8_t speed) {
	ssd1306_chip_select();
	ssd1306_enable_command();
	ssd1306_write_byte(0x29);
	ssd1306_write_byte(0x00);
	ssd1306_write_byte(start);
	ssd1306_write_byte(0x0f); // 值越大，刷新的频率越快
	ssd1306_write_byte(end);
	ssd1306_write_byte(0x02); // 每次刷新，上移的行数
	ssd1306_write_byte(0x2f);
	ssd1306_chip_deselect();
}

void oled_scroll_down(uint8_t start, uint8_t end, uint8_t speed) {
	ssd1306_chip_select();
	ssd1306_enable_command();
	ssd1306_write_byte(0x2a);
	ssd1306_write_byte(0x00);
	ssd1306_write_byte(start);
	ssd1306_write_byte(0x00);
	ssd1306_write_byte(end);
	ssd1306_write_byte(0x02);
	ssd1306_write_byte(0x2f);
	ssd1306_chip_deselect();
}


void oled_write_data(const uint8_t *data, uint8_t size) {
	uint8_t i;
	ssd1306_chip_select();
	ssd1306_enable_data();
	for (i=0; i<size; i++) {
		ssd1306_write_byte(data[i]);
	}
	ssd1306_chip_deselect();
}

void oled_write_byte(uint8_t data) {
	ssd1306_chip_select();
	ssd1306_enable_data();
	ssd1306_write_byte(data);
	ssd1306_chip_deselect();
}
