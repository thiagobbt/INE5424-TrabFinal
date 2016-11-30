#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "altera_up_avalon_parallel_port.h"
#include "altera_up_avalon_character_lcd.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"

/*
 * This stucture holds a pointer to each of the open devices
 */
struct alt_up_dev {
    alt_up_parallel_port_dev    *KEY_dev;
    alt_up_parallel_port_dev    *switch_dev;
    alt_up_character_lcd_dev    *lcd_dev;
    alt_up_char_buffer_dev      *char_buffer_dev;
    alt_up_pixel_buffer_dma_dev *pixel_buffer_dev;
};

class System {
 public:
	System();
	int execute();
	void setTimeout();
	void clearTimerInterrupt();
	int readKeys();
	void clearKeysInterrupt();
	int readSwitches();
	void clearSwitchesInterrupt();

	alt_up_dev& getDevices();

 private:
	void initVars();
	bool initDevices();
	void init();
	void onInterrupt();

	static volatile int* const interval_timer_ptr;
	static char text[40];
	static char text_erase[40];
	static volatile int timeout; // used to synchronize with the timer

	alt_up_parallel_port_dev* KEY_dev;
	alt_up_parallel_port_dev* switch_dev;
	alt_up_character_lcd_dev* lcd_dev;
	alt_up_char_buffer_dev* char_buffer_dev;
	alt_up_pixel_buffer_dma_dev* pixel_buffer_dev;
	alt_up_dev up_dev; // struct to hold pointers to open devices

	int last_row;
	int last_column;
};

#endif
