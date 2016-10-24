#include "nios2_ctrl_reg_macros.h"
#include "pointers.h"
#include "utils.h"

/* these globals are written by interrupt service routines;
we have to declare 
 * these as volatile to avoid the compiler caching their values in registers */
extern volatile char byte1, byte2, byte3;			// modified by PS/2 interrupt service routine
extern volatile int timeout;						// used to synchronize with the timer

char text[40] = "Operating Systems II\0";
unsigned int text_length;
char text_erase[40] = "";

void init_vars();
void init();
void interrupt_handler();

int main() {
	init();

	// create a messages to be displayed on the VGA and LCD displays
	char text_top_LCD[80] = "Welcome to the DE2 Media Computer...\0";

	// output text message to the LCD
	LCD_cursor(0,0);			// set LCD cursor location to top row
	LCD_text(text_top_LCD);
	LCD_cursor_off();			// turn off the LCD cursor 

	// the following variables give the size of the pixel buffer
	int screen_x = 319;
	int screen_y = 239;
	short color = 0x1863;		// a dark grey color
	VGA_box(0, 0, screen_x, screen_y, color);	// fill the screen with grey
	VGA_text(0, 0, text);

	while (1) {
		while (!timeout); // wait to synchronize with timer 
		interrupt_handler();
	}
}

void init_vars() {
	timeout = 0;	// synchronize with the timer
	text_length = 20;

	for (int i = 0; i < text_length; i++) {
		text_erase[i] = ' ';
	}
	text_erase[text_length] = '\0';
}

void init() {
	init_vars();

	// set the interval timer period for scrolling the HEX displays
	int counter = 0x960000;				// 1/(50 MHz) x (0x960000) ~= 200 msec
	*(interval_timer_ptr + 0x2) = (counter & 0xFFFF);
	*(interval_timer_ptr + 0x3) = (counter >> 16) & 0xFFFF;

	// start interval timer, enable its interrupts
	*(interval_timer_ptr + 1) = 0x7;	// STOP = 0, START = 1, CONT = 1, ITO = 1 
	*(KEY_ptr + 2) = 0xE;			/* write to the pushbutton interrupt mask register, and
									 * set 3 mask bits to 1 (bit 0 is Nios II reset) */
	*(PS2_ptr) = 0xFF;				// reset
	*(PS2_ptr + 1) = 0x1;			// write to the PS/2 Control register to enable interrupts

	NIOS2_WRITE_IENABLE(0xC3);	/* set interrupt mask bits for levels 0 (interval
								 * timer), 1 (pushbuttons), 6 (audio), and 7 (PS/2) */
	NIOS2_WRITE_STATUS(1);		// enable Nios II interrupts
}

void interrupt_handler() {
	// display PS/2 data (from interrupt service routine) on HEX displays
	// HEX_PS2(byte1, byte2, byte3);
	char values[] = {1, 2, 3, 4, 5, 6, 7, 8};
	display7seg(values);
	timeout = 0;
}
