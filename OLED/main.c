#include <msp430.h>
#include <stdbool.h>
#include "ssd1306.h"
#include "app.h"

void main(void) {

	oled_init();

	oled_clear_screen();

	char msg[] = "@ABCDEFGHIGKLMNOPQRSTUVWXYZ[\\]^_abcdefghiklmnopqrstuvwxyz";

	oled_set_position(2, 16);

	oled_show_string(msg);

	int i = 5;
	while(i--) {
		__delay_cycles(200);
	}
}
