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
void interrupt_callback();

int main() {
	init();

	// output text message to the LCD
	LCD_cursor_off();

	short color = 0x1863;		// a dark grey color
	VGA_draw_filled_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color);
	VGA_text(0, 0, text);

	clear7seg();

	while (1) {
		while (!timeout); // wait to synchronize with timer 
		interrupt_callback();
	}
}

void init_vars() {
	timeout = 0;	// synchronize with the timer
	text_length = 20;

	int i;
	for (i = 0; i < text_length; i++) {
		text_erase[i] = ' ';
	}
	text_erase[text_length] = '\0';
}

void init() {
	init_vars();
	init_colors();

	// set the interval timer period for scrolling the HEX displays
	int counter = 0x960000;				// 1/(50 MHz) x (0x960000) ~= 200 msec
	*(interval_timer_ptr + 0x2) = (counter & 0xFFFF);
	*(interval_timer_ptr + 0x3) = (counter >> 16) & 0xFFFF;

	// start interval timer, enable its interrupts
	*(interval_timer_ptr + 1) = 0x7;	// STOP = 0, START = 1, CONT = 1, ITO = 1 
	*(KEY_ptr + 2) = 0xF;			/* write to the pushbutton interrupt mask register, and
									 * set 3 mask bits to 1 (bit 0 is Nios II reset) */
	*(PS2_ptr) = 0xFF;				// reset
	*(PS2_ptr + 1) = 0x1;			// write to the PS/2 Control register to enable interrupts

	NIOS2_WRITE_IENABLE(0xC3);	/* set interrupt mask bits for levels 
								 * 0 (interval timer)
								 * 1 (pushbuttons)
								 * 6 (audio)
								 * 7 (PS/2)
								 */
	NIOS2_WRITE_STATUS(1);		// enable Nios II interrupts
}

int last_row = -1;
int last_column = -1;
void interrupt_callback() {
	int SWITCH_value;
	SWITCH_value = *SWITCH_ptr;

	int row = (SWITCH_value & 0x3fe00) >> 9;
	int column = SWITCH_value & 0x001ff;

	char left_text[10];
	itoa(row, left_text, 10);

	char right_text[10];
	itoa(column, right_text, 10);

	if (row != last_row || column != last_column) {
		LCD_clear();
		LCD_text("Row = ");
		LCD_text(left_text);
		LCD_cursor(15, 0);
		switch (color) {
			case -2048: LCD_text("R"); break;
			case 2016: LCD_text("G"); break;
			case 31: LCD_text("B"); break;
		}

		LCD_cursor(14, 0);
		if (fill_mode) {
			LCD_text("F");
		} else {
			LCD_text(" ");
		}

		LCD_cursor(0, 1);
		LCD_text("Column = ");
		LCD_text(right_text);
		last_row = row;
		last_column = column;
	}
}
