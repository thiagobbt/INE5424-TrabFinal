#include "sys/alt_stdio.h"
#include "VGA.hpp"
#include "Traits.hpp"

short red;
short green;
short blue;
short color;
short rect_mode = 0;
short fill_mode = 0;

void display7seg(char values[8]) {
	const unsigned char seven_seg_decode_table[] = {
		0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
		0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71
	};

	const unsigned size = 8;
	unsigned char hex_segs[] = {0, 0, 0, 0, 0, 0, 0, 0};
	unsigned shift_buffer = 0;
	unsigned shift = 28;

	for (unsigned i = 0; i < size; i++) {
		if (values[i] != -1) {
			shift_buffer |= values[i] << shift;
		}
		shift -= 4;
	}

	for (unsigned i = 0; i < size; i++) {
		unsigned char nibble = shift_buffer & 0x0000000F;
		unsigned char code = seven_seg_decode_table[nibble];
		unsigned reversed = size - 1 - i;
		if (values[reversed] != -1) {
			hex_segs[i] = code;
		}
		shift_buffer = shift_buffer >> 4;
	}

	/* drive the hex displays */
	volatile int* HEX3_HEX0_ptr = (int*) 0x10000020;
	volatile int* HEX7_HEX4_ptr = (int*) 0x10000030;
	*(HEX3_HEX0_ptr) = *(int*) (hex_segs);
	*(HEX7_HEX4_ptr) = *(int*) (hex_segs+4);
}

void clear7seg() {
	char values[] = {0, 0, 0, 0, 0, 0, 0, 0};
	display7seg(values);
}

float absolute(float n) {
	return n > 0 ? n : -n;
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

void init_colors() {
	red = VGA::getColor(0xFF, 0x00, 0x00);
	green = VGA::getColor(0x00, 0xFF, 0x00);
	blue = VGA::getColor(0x00, 0x00, 0xFF);
	color = red;
}
