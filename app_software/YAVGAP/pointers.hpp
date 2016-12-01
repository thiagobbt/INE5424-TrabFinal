#ifndef POINTER_HPP
#define POINTER_HPP

namespace ptr {
	volatile int*   const PS2_ptr				= (int*)   0x10000100;
	volatile int*   const interval_timer_ptr	= (int*)   0x10002000;
	volatile int*   const KEY_ptr				= (int*)   0x10000050;
	volatile int*   const SWITCH_ptr			= (int*)   0x10000040;
	volatile int*   const HEX3_HEX0_ptr		= (int*)   0x10000020;
	volatile int*   const HEX7_HEX4_ptr		= (int*)   0x10000030;
	volatile char*  const LCD_display_ptr		= (char*)  0x10003050;
	volatile char*  const character_buffer	= (char*)  0x09000000;
	volatile short* const pixel_buffer		= (short*) 0x08000000;
}

#endif
