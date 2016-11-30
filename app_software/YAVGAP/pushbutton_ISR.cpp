#include "LCD.hpp"
#include "Traits.hpp"
#include "utils.hpp"
#include "VGA.hpp"

const int KEY0 = 0x0;
const int KEY1 = 0x2;
const int KEY2 = 0x4;
const int KEY3 = 0x8;

int line_x1 = -1;
int line_y1 = -1;
int rect_x1 = -1;
int rect_y1 = -1;

void display_coords(int row, int column) {
	int row_hundreds = row / 100;
	int row_tens = (row - 100 * row_hundreds) / 10;
	int row_ones = row - 100 * row_hundreds - 10 * row_tens;
	int column_hundreds = column / 100;
	int column_tens = (column - 100 * column_hundreds) / 10;
	int column_ones = column - 100 * column_hundreds - 10 * column_tens;
	char values[] = {
		0, row_hundreds, row_tens, row_ones,
		0, column_hundreds, column_tens, column_ones
	};
	display7seg(values);
}

void draw_olympic_logo() {
	VGA::drawFilledRect(10, 60, 160, 180, VGA::getColor(40, 40, 40));

	VGA::drawCircle( 50, 100, 30, VGA::getColor(0xFF, 0x00, 0x00));
	VGA::drawCircle( 80, 100, 30, VGA::getColor(0x00, 0xFF, 0x00));
	VGA::drawCircle(120, 100, 30, VGA::getColor(0x00, 0x00, 0xFE));
	VGA::drawCircle( 65, 140, 30, VGA::getColor(0xFF, 0xFF, 0x00));
	VGA::drawCircle(100, 140, 30, VGA::getColor(0x00, 0x00, 0x00));
}

void clear_memory() {
	line_x1 = -1;
	line_y1 = -1;
	rect_x1 = -1;
	rect_y1 = -1;
	clear7seg();
}

void key1(int row, int column) {
	clear_memory();
	if (row == 0 && column == 0) {
		VGA::clearScreen();
	} else if (row == 256 && column == 256) {
		draw_olympic_logo();
	} else if (column == 256) {
		VGA::textClearLine(row);
	} else if (row == 256) {
		switch (column) {
			case 1:
				color = blue;
				LCD::cursor(15, 0);
				LCD::text("B");
				break;
			case 2:
				color = green;
				LCD::cursor(15, 0);
				LCD::text("G");
				break;
			case 4:
				color = red;
				LCD::cursor(15, 0);
				LCD::text("R");
				break;
			case 8:
				rect_mode = 1 - rect_mode;
				LCD::cursor(15, 1);
				if (rect_mode) {
					LCD::text("R");
				} else {
					LCD::text("L");
				}
				break;
			case 16:
				fill_mode = 1 - fill_mode;
				LCD::cursor(14, 0);
				if (fill_mode) {
					LCD::text("F");
				} else {
					LCD::text(" ");
				}
				break;
		}
	} else {
		VGA::text(column, row, "INE5424\0");
	}
}

void key2(int row, int column) {
	if (rect_mode) {
		if (rect_x1 == -1) {
			clear_memory();
			rect_x1 = column;
			rect_y1 = row;
			display_coords(row, column);
		} else {
			if (fill_mode) {
				VGA::drawFilledRect(rect_x1, rect_y1, column, row, color);
			} else {
				VGA::drawRect(rect_x1, rect_y1, column, row, color);
			}
			display_coords(0, 0);
			clear_memory();
		}
	} else {
		if (line_x1 == -1) {
			clear_memory();
			line_x1 = column;
			line_y1 = row;
			display_coords(row, column);
		} else {
			VGA::drawLine(line_x1, line_y1, column, row, color);
			display_coords(0, 0);
			clear_memory();
		}
	}
}

/***************************************************************************************
 * Pushbutton - Interrupt Service Routine                                
 *                                                                          
 * This routine checks which KEY has been pressed. If it is KEline_Y1 or KEY2, it writes this
 * value to the global variable key_pressed. If it is KEY3 then it loads the SW switch 
 * values and stores in the variable pattern
****************************************************************************************/
void pushbutton_ISR() {
	int KEY_value = Traits::system.readKeys();
	int SWITCH_value = Traits::system.readSwitches();

	int row = (SWITCH_value & 0x3fe00) >> 9;
	int column = SWITCH_value & 0x001ff;

	if (KEY_value == KEY1) {
		key1(row, column);
	} else if (KEY_value == KEY2) {
		key2(row, column);
	} else if (KEY_value == KEY3) {
		if (fill_mode) {
			VGA::drawFilledCircle(column, row, 30, color);
		} else {
			VGA::drawCircle(column, row, 30, color);
		}
		clear_memory();
	}
}
