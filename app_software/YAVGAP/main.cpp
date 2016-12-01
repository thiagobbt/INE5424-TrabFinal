#include "System.hpp"
#include "utils.hpp"

unsigned int text_length;

volatile int buf_index_record, buf_index_play; // audio variables
volatile unsigned char byte1, byte2, byte3;    // PS/2 variables

int main() {
	utils::initColors();
	System system;
	return system.execute();
}
