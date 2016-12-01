#include "interval_timer_ISR.hpp"
#include "LCD.hpp"
#include "pointers.hpp"
#include "pushbutton_ISR.hpp"
#include "nios2_ctrl_reg_macros.hpp"
#include "System.hpp"
#include "sys/alt_irq.h"
#include "sys/alt_stdio.h"
#include "utils.hpp"
#include "VGA.hpp"

char System::text[40] = "Operating Systems II\0";
char System::text_erase[40] = "";
volatile int System::timeout;

System::System() : last_row(-1), last_column(-1) {
	init();
}

int System::execute() {
	// output text message to the LCD
	LCD::cursorOff();

	short color = 0x1863;		// a dark grey color
	VGA::drawFilledRect(0, 0, VGA::SCREEN_WIDTH, VGA::SCREEN_HEIGHT, color);
	VGA::text(0, 0, text);

	utils::clear7seg();


	while (1) {
		while (!timeout); // wait to synchronize with timer 
		onInterrupt();
	}
}

void System::setTimeout() {
	timeout = 1;
}

void System::clearTimerInterrupt() {
	*(ptr::interval_timer_ptr) = 0;
}

int System::readKeys() {
    return alt_up_parallel_port_read_edge_capture(up_dev.KEY_dev);
}

void System::clearKeysInterrupt() {
    alt_up_parallel_port_clear_edge_capture(up_dev.KEY_dev);
}

int System::readSwitches() {
    return alt_up_parallel_port_read_edge_capture(up_dev.switch_dev);
}

void System::clearSwitchesInterrupt() {
    alt_up_parallel_port_clear_edge_capture(up_dev.switch_dev);
}

alt_up_dev& System::getDevices() {
	return up_dev;
}

void System::initVars() {
	timeout = 0;	// synchronize with the timer
	size_t text_length = 20;

	for (size_t i = 0; i < text_length; i++) {
		text_erase[i] = ' ';
	}
	text_erase[text_length] = '\0';
}

bool System::initDevices() {
    // lcd_dev = alt_up_character_lcd_open_dev("/dev/Char_LCD_16x2");
    // if (lcd_dev == NULL) {
    //     alt_printf("Error: could not open character LCD device\n");
    //     return false;
    // } else {
    //     alt_printf("Opened character LCD device\n");
    // }

    // pixel_buffer_dev = alt_up_pixel_buffer_dma_open_dev("/dev/VGA_Pixel_Buffer");
    // if (pixel_buffer_dev == NULL) alt_printf("Error: could not open pixel buffer device\n");
    // else alt_printf("Opened pixel buffer device\n");

    // char_buffer_dev = alt_up_char_buffer_open_dev("/dev/VGA_Char_Buffer");
    // if (char_buffer_dev == NULL) alt_printf("Error: could not open character buffer device\n");
    // else alt_printf("Opened character buffer device\n");

    // KEY_dev = alt_up_parallel_port_open_dev("/dev/Pushbuttons");
    // if (KEY_dev == NULL) {
    //     alt_printf("Error: could not open pushbutton KEY device\n");
    //     return false;
    // } else {
    //     alt_printf("Opened pushbutton KEY device\n");
    //     up_dev.KEY_dev = KEY_dev;
    // }

    // switch_dev = alt_up_parallel_port_open_dev("/dev/Slider_Switches");
    // if (switch_dev == NULL) {
    //     alt_printf("Error: could not open switches\n");
    //     return false;
    // } else {
    //     alt_printf("Opened switches\n");
    //     up_dev.switch_dev = switch_dev;
    // }

    return true;
}

void System::init() {
	initVars();
	initDevices();

	// set the interval timer period for scrolling the HEX displays
	int counter = 0x960000;				// 1/(50 MHz) x (0x960000) ~= 200 msec
	*(ptr::interval_timer_ptr + 0x2) = (counter & 0xFFFF);
	*(ptr::interval_timer_ptr + 0x3) = (counter >> 16) & 0xFFFF;

	// start interval timer, enable its interrupts
	*(ptr::interval_timer_ptr + 1) = 0x7;	// STOP = 0, START = 1, CONT = 1, ITO = 1 
	*(ptr::KEY_ptr + 2) = 0xE;			/* write to the pushbutton interrupt mask register, and
									 * set 3 mask bits to 1 (bit 0 is Nios II reset) */
	*(ptr::PS2_ptr) = 0xFF;				// reset
	*(ptr::PS2_ptr + 1) = 0x1;			// write to the PS/2 Control register to enable interrupts

	NIOS2_WRITE_IENABLE(0xC3);	/* set interrupt mask bits for levels 
								 * 0 (interval timer)
								 * 1 (pushbuttons)
								 * 6 (audio)
								 * 7 (PS/2)
								 */
	NIOS2_WRITE_STATUS(1);		// enable Nios II interrupts
}

void System::onInterrupt() {
	// int SWITCH_value;
	// SWITCH_value = *SWITCH_ptr;
    int SWITCH_value = readSwitches();
    clearSwitchesInterrupt();

	int row = (SWITCH_value & 0x3fe00) >> 9;
	int column = SWITCH_value & 0x001ff;

	char left_text[10];
	utils::itoa(row, left_text, 10);

	char right_text[10];
	utils::itoa(column, right_text, 10);

	if (row != last_row || column != last_column) {
		LCD::clear();
		LCD::text("Row = ");
		LCD::text(left_text);
		LCD::cursor(15, 0);
		switch (color) {
			case -2048: LCD::text("R"); break;
			case 2016: LCD::text("G"); break;
			case 31: LCD::text("B"); break;
		}

		LCD::cursor(15, 1);
		if (rect_mode) {
			LCD::text("R");
		} else {
			LCD::text("L");
		}

		LCD::cursor(14, 0);
		if (fill_mode) {
			LCD::text("F");
		} else {
			LCD::text(" ");
		}

		LCD::cursor(0, 1);
		LCD::text("Column = ");
		LCD::text(right_text);
		last_row = row;
		last_column = column;
	}
}
