#include <msp430.h>
#include <stdbool.h>
#include "ssd1306.h"

void main(void) {

	oled_init();
	oled_display_off();
	oled_enable_charge_pump();

	oled_set_multiplex_ratio(0x20);
	//oled_set_display_offset(0x00);
	//oled_set_display_start_line(0x00);
	//oled_set_normal_display();

	oled_display_on();

	int i= 5;
	while(i--) {
		  __delay_cycles(200);
	}

	oled_display_off();

	oled_display_on();

 
}
