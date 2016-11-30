#ifndef LCD_HPP
#define LCD_HPP

#include "Traits.hpp"

class LCD {
 public:
	static void cursor(int x, int y) {
		// char instruction = x;
		// if (y != 0) instruction |= 0x40;			// set bit 6 for bottom row
		// instruction |= 0x80;						// need to set bit 7 to set the cursor location
		// *(LCD_display_ptr) = instruction;			// write to the LCD instruction register
		alt_up_character_lcd_set_cursor_pos(Traits::system.getDevices().lcd_dev, x, y);
	}

	static void text(char* text_ptr) {
		// while (*(text_ptr)) {
		// 	*(LCD_display_ptr + 1) = *(text_ptr);	// write to the LCD data register
		// 	++text_ptr;
		// }
		alt_up_character_lcd_string(Traits::system.getDevices().lcd_dev, text_ptr);
	}

	static void clear() {
		// *(LCD_display_ptr) = 0x01;
		// LCD_text("                ");
		alt_up_character_lcd_init(Traits::system.getDevices().lcd_dev);
	}

	static void cursorOff() {
		// *(LCD_display_ptr) = 0x0C;
		alt_up_character_lcd_cursor_off(Traits::system.getDevices().lcd_dev);
	}	
};

#endif
