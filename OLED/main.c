#include <msp430.h>
#include <stdbool.h>
#include "ssd1306.h"
#include "app.h"

void main(void) {

	oled_init();
	oled_set_memory_mode(PAGE_MODE);
	oled_clear_screen();
	oled_scroll_deactive();
	char msg[] = "ABC";
	int i = 5;
	for (i=5; i>0; i--) {
		oled_set_position(i, 16);
		oled_show_string(msg);
	}

	oled_scroll_right(0, 2);
	oled_scroll_left(3, 4);

	i = 5;
	while(i--) {
		__delay_cycles(200);
	}
}
