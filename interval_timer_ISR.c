#include "pointers.h"

extern volatile int timeout;

/*****************************************************************************
 * Interval timer interrupt service routine
 *                                                                          
 * Controls refresh of the VGA screen
 * 
******************************************************************************/
void interval_timer_ISR() {
	*(interval_timer_ptr) = 0; 										// clear the interrupt
	timeout = 1;															// set global variable

	/* shift the LCD display to the left */
	*(LCD_display_ptr) = 0x18;	// instruction = shift left
}

