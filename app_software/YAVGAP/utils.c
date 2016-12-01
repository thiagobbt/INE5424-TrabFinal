#include "pointers.h"

#define bool int
#define true 1
#define false 0

int SCREEN_WIDTH = 319;
int SCREEN_HEIGHT = 239;

short red;
short green;
short blue;
short color;
short fill_mode = 0;

void display7seg(char values[8]) {
	unsigned char seven_seg_decode_table[] = {
		0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
		0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71
	};

	unsigned char hex_segs[] = {0, 0, 0, 0, 0, 0, 0, 0};
	unsigned int shift_buffer = 0;
	unsigned int shift = 28;
	unsigned int size = 8;

	int i;
	for (i = 0; i < size; i++) {
		if (values[i] != -1) {
			shift_buffer |= values[i] << shift;
		}
		shift -= 4;
	}

	for (i = 0; i < size; i++) {
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

void clear7seg() {
	char values[] = {0, 0, 0, 0, 0, 0, 0, 0};
	display7seg(values);
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

void LCD_clear() {
	*(LCD_display_ptr) = 0x01;
}

void LCD_cursor_off() {
	*(LCD_display_ptr) = 0x0C;
}

short VGA_get_color(unsigned char R, unsigned char G, unsigned char B) {
	return ((R * 31 / 255) << 11) |
		   ((G * 63 / 255) << 5) |
		   ((B * 31 / 254));
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

void VGA_text_clear_line(int n) {
	char* nothing = "                                                                                \0";
	VGA_text(0, n, nothing);
}

void VGA_text_clear() {
	int i;
	for (i = 0; i < 60; ++i)	{
		VGA_text_clear_line(i);
	}
}

inline void VGA_draw_pixel(int x, int y, short pixel_color) {
	int offset = (y << 9) + x;
	*(pixel_buffer + offset) = pixel_color;
}

float absolute(float n) {
	return n > 0 ? n : -n;
}

void VGA_draw_line(int x1, int y1, int x2, int y2, short pixel_color) {
	float dx = x2 - x1;
	float dy = y2 - y1;

	int x, y;

	if (dx == 0) {
		y = y1;
		while (y <= y2) {
			VGA_draw_pixel(x1, y, pixel_color);
			y++;
		}
		return;
	}

	float error = 0;
	float derror = absolute(dy/dx);

	if (dx < 0) {
		int aux = x1;
		x1 = x2;
		x2 = aux;

		aux = y1;
		y1 = y2;
		y2 = aux;
	}

	y = y1;
	for (x = x1; x < x2; x++) {
		VGA_draw_pixel(x, y, pixel_color);
		error += derror;

		if (error > 0) {
			y++;
			error--;
		}
	}
}

void VGA_draw_filled_rect(int x1, int y1, int x2, int y2, short pixel_color) {
	int row, col;
	// assume that the box coordinates are valid
	for (row = y1; row <= y2; row++) {
		for (col = x1; col <= x2; col++) {
			VGA_draw_pixel(col, row, pixel_color);
		}
	}
}

void VGA_draw_rect(int x1, int y1, int x2, int y2, short pixel_color) {
	VGA_draw_line(x1, y1, x2, y1, pixel_color);
	VGA_draw_line(x2, y1, x2, y2, pixel_color);
	VGA_draw_line(x1, y2, x2, y2, pixel_color);
	VGA_draw_line(x1, y1, x1, y2, pixel_color);
}

void reverse(char str[], int length) {
	int start = 0;
	int end = length -1;
	while (start < end) {
		*(str+start) = *(str+start) ^ *(str+end);
		*(str+end) = *(str+start) ^ *(str+end);
		*(str+start) = *(str+end) ^ *(str+start);

		start++;
		end--;
	}
}

char* itoa(int num, char* str, int base) {
	int i = 0;
	bool isNegative = false;

	/* Handle 0 explicitly, otherwise empty string is printed for 0 */
	if (num == 0) {
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}

	// In standard itoa(), negative numbers are handled only with
	// base 10. Otherwise numbers are considered unsigned.
	if (num < 0 && base == 10) {
		isNegative = true;
		num = -num;
	}

	// Process individual digits
	while (num != 0) {
		int rem = num % base;
		str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
		num = num/base;
	}

	// If number is negative, append '-'
	if (isNegative)
		str[i++] = '-';

	str[i] = '\0'; // Append string terminator

	// Reverse the string
	reverse(str, i);

	return str;
}

void VGA_draw_circle(int xc, int yc, int radius, short pixel_color) {
	int x = radius;
	int y = 0;
	int err = 0;

	while (x >= y) {
		VGA_draw_pixel(xc + x, yc + y, pixel_color);
		VGA_draw_pixel(xc + y, yc + x, pixel_color);
		VGA_draw_pixel(xc - y, yc + x, pixel_color);
		VGA_draw_pixel(xc - x, yc + y, pixel_color);
		VGA_draw_pixel(xc - x, yc - y, pixel_color);
		VGA_draw_pixel(xc - y, yc - x, pixel_color);
		VGA_draw_pixel(xc + y, yc - x, pixel_color);
		VGA_draw_pixel(xc + x, yc - y, pixel_color);
		y++;
		err += 1 + 2 * y;
		if (2 * (err - x) + 1 > 0) {
			x--;
			err += 1 - 2 * x;
		}
	}
}

void VGA_draw_filled_circle (int xc, int yc, int radius, short pixel_color) {
	int y, x;
	for (y = -radius; y <= radius; y++) {
		for (x = -radius; x <= radius; x++) {
			if ((x * x) + (y * y) <= (radius * radius)) {
				VGA_draw_pixel(x + xc, y + yc, pixel_color);
			}
		}
	}
}

void VGA_clear_screen() {
	VGA_text_clear();
	VGA_draw_filled_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x00);
}

void init_colors() {
	red = VGA_get_color(0xFF, 0x00, 0x00);
	green = VGA_get_color(0x00, 0xFF, 0x00);
	blue = VGA_get_color(0x00, 0x00, 0xFF);
	color = red;
}
