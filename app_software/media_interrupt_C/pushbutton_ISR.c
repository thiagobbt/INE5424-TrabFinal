#include "utils.h"
#include "pointers.h"

#define bool int
#define true 1
#define false 0

/* A utility function to reverse a string  */
void reverse(char str[], int length) {
	int start = 0;
	int end = length -1;
	while (start < end) {
		//swap(*(str+start), *(str+end));
		*(str+start) = *(str+start) ^ *(str+end);
		*(str+end) = *(str+start) ^ *(str+end);
		*(str+start) = *(str+end) ^ *(str+start);

		start++;
		end--;
	}
}

// Implementation of itoa()
char* itoa(int num, char* str, int base) {
	int i = 0;
	bool isNegative = false;

	/* Handle 0 explicitely, otherwise empty string is printed for 0 */
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

/***************************************************************************************
 * Pushbutton - Interrupt Service Routine                                
 *                                                                          
 * This routine checks which KEY has been pressed. If it is KEY1 or KEY2, it writes this 
 * value to the global variable key_pressed. If it is KEY3 then it loads the SW switch 
 * values and stores in the variable pattern
****************************************************************************************/
void pushbutton_ISR() {
	int KEY_value;

	KEY_value = *(KEY_ptr + 3);         // read the pushbutton interrupt register
	*(KEY_ptr + 3) = 0;                         // Clear the interrupt
	char sup[] = "Hallo\0";

	if (KEY_value == 0x2) {
		// check KEY1
		VGA_clear_screen();
		LCD_clear();
	} else if (KEY_value == 0x4) {
		// check KEY2
		VGA_draw_line(10, 10, 100, 10, 0xFF);
		VGA_draw_line(10, 10, 100, 100, VGA_get_color(0xFF, 0x00, 0x00));
	} else if (KEY_value == 0x8) {
		// check KEY3

		// Draw Olympic logo (kinda)
		VGA_box(10, 60, 180, 180, VGA_get_color(40, 40, 40));

		VGA_draw_circle( 50, 100, 30, VGA_get_color(0xFF, 0x00, 0x00));
		VGA_draw_circle( 80, 100, 30, VGA_get_color(0x00, 0xFF, 0x00));
		VGA_draw_circle(120, 100, 30, VGA_get_color(0x00, 0x00, 0xFE));
		VGA_draw_circle( 65, 140, 30, VGA_get_color(0xFF, 0xFF, 0x00));
		VGA_draw_circle(100, 140, 30, VGA_get_color(0x00, 0x00, 0x00));
	}
}
