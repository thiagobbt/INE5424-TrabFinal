#include "Traits.hpp"

extern volatile int timeout;

/*****************************************************************************
 * Interval timer interrupt service routine
 *                                                                          
 * Controls refresh of the VGA screen
 * 
******************************************************************************/
void interval_timer_ISR() {
	Traits::system.clearTimerInterrupt();
	Traits::system.setTimeout();
}
