#ifndef LCD_HPP
#define LCD_HPP

#include "pointers.hpp"
#include "Traits.hpp"

namespace LCD {
	inline void cursor(int x, int y) {
		char instruction = x;
		if (y != 0) instruction |= 0x40;			// set bit 6 for bottom row
		instruction |= 0x80;						// need to set bit 7 to set the cursor location
		*(ptr::LCD_display_ptr) = instruction;			// write to the LCD instruction register
	}

	inline void text(char* text_ptr) {
		while (*(text_ptr)) {
			*(ptr::LCD_display_ptr + 1) = *(text_ptr);	// write to the LCD data register
			++text_ptr;
		}
	}

	inline void clear() {
		*(ptr::LCD_display_ptr) = 0x01;
		text("                ");
	}

	inline void cursorOff() {
		*(ptr::LCD_display_ptr) = 0x0C;
	}	
};

#endif
