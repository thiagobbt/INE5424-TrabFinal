#include "utils.h"
#include "pointers.h"

/***************************************************************************************
 * Pushbutton - Interrupt Service Routine                                
 *                                                                          
 * This routine checks which KEY has been pressed. If it is KEY1 or KEY2, it writes this 
 * value to the global variable key_pressed. If it is KEY3 then it loads the SW switch 
 * values and stores in the variable pattern
****************************************************************************************/
void pushbutton_ISR() {	
	int KEY_value;

	KEY_value = *(KEY_ptr + 3);			// read the pushbutton interrupt register
	*(KEY_ptr + 3) = 0; 						// Clear the interrupt
	char sup[] = "Hallo\0";

	if (KEY_value == 0x2) {
		// check KEY1 {
		//VGA_text_clear();
		VGA_clear_screen();
	} else if (KEY_value == 0x4) {
		// check KEY2
		VGA_draw_line(10, 10, 100, 10, 0xFF);
	} else if (KEY_value == 0x8) {
		// check KEY3
		VGA_draw_filled_circle(10, 10, 5, 0xFF);
	}
}
