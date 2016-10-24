#include "pointers.h"

void display7seg(char values[8]) {
	unsigned char seven_seg_decode_table[] = {
		0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
		0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71
	};

	unsigned char hex_segs[] = {0, 0, 0, 0, 0, 0, 0, 0};
	unsigned int shift_buffer = 0;
	unsigned int shift = 28;
	unsigned int size = 8;
	for (int i = 0; i < size; i++) {
		if (values[i] != -1) {
			shift_buffer |= values[i] << shift;
		}
		shift -= 4;
	}

	for (int i = 0; i < size; i++) {
		unsigned char nibble = shift_buffer & 0x0000000F;
		unsigned char code = seven_seg_decode_table[nibble];
		unsigned int reversed = size - 1 - i;
		if (values[reversed] != -1) {
			hex_segs[i] = code;
		}
		shift_buffer = shift_buffer >> 4;
	}
	/* drive the hex displays */
	*(HEX3_HEX0_ptr) = *(int*) (hex_segs);
	*(HEX7_HEX4_ptr) = *(int*) (hex_segs+4);
}

void LCD_cursor(int x, int y) {
	char instruction = x;
	if (y != 0) instruction |= 0x40;			// set bit 6 for bottom row
	instruction |= 0x80;						// need to set bit 7 to set the cursor location
	*(LCD_display_ptr) = instruction;			// write to the LCD instruction register
}

void LCD_text(char* text_ptr) {
	while (*(text_ptr)) {
		*(LCD_display_ptr + 1) = *(text_ptr);	// write to the LCD data register
		++text_ptr;
	}
}

void LCD_cursor_off() {
	*(LCD_display_ptr) = 0x0C;
}

void VGA_text(int x, int y, char* text_ptr) {
	// assume that the text string fits on one line
	int offset = (y << 7) + x;
	while (*(text_ptr)) {
		*(character_buffer + offset) = *(text_ptr);	// write to the character buffer
		++text_ptr;
		++offset;
	}
}

void VGA_box(int x1, int y1, int x2, int y2, short pixel_color) {
	// assume that the box coordinates are valid
	for (int row = y1; row <= y2; row++) {
		for (int col = x1; col <= x2; col++) {
			int offset = (row << 9) + col;
			*(pixel_buffer + offset) = pixel_color;	// compute halfword address, set pixel
		}
	}
}
