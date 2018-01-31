#include <msp430.h>
#include <stdbool.h>
#include "ssd1306.h"
#include "app.h"

void main(void) {

	oled_init();
	oled_set_memory_mode(PAGE_MODE);
	oled_clear_screen();
	char msg[] = "ABCCDEFGH";
	oled_set_position(1, 16);
	oled_show_string(msg);
	int i = 5;

	//oled_vertial_scroll_range(0, 64);
	///oled_scroll_up(2, 3);
	oled_scroll_up(1, 6, 0x0f);
	//oled_scroll_right(1, 3);

	i = 5;
	while(i--) {
		__delay_cycles(200);
	}
}
