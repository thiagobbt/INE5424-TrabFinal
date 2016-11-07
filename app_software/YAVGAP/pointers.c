// #include "pointers.h"

volatile int*   PS2_ptr				= (int*)   0x10000100;
volatile int*   interval_timer_ptr	= (int*)   0x10002000;
volatile int*   KEY_ptr				= (int*)   0x10000050;
volatile int*	SWITCH_ptr			= (int*)   0x10000040;
volatile int*   HEX3_HEX0_ptr		= (int*)   0x10000020;
volatile int*   HEX7_HEX4_ptr		= (int*)   0x10000030;
volatile char*  LCD_display_ptr		= (char*)  0x10003050;
volatile char*  character_buffer	= (char*)  0x09000000;
volatile short* pixel_buffer		= (short*) 0x08000000;
