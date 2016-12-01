// the following variables give the size of the pixel buffer
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern short red;
extern short green;
extern short blue;
extern short color;

extern short rect_mode;
extern short fill_mode;

namespace utils {
	/****************************************************************************************
	 * Reverses a string
	 ****************************************************************************************/
	void reverse(char str[], int length);

	/****************************************************************************************
	 * Converts a number to a char*
	 ****************************************************************************************/
	char* itoa(int num, char* str, int base);

	/****************************************************************************************
	 * Displays hexadecimal numbers to the 7 segment displays
	 ****************************************************************************************/
	void display7seg(char values[8]);

	/****************************************************************************************
	 * Zeroes the 7 segment displays
	 ****************************************************************************************/
	void clear7seg();

	/****************************************************************************************
	 * Initializes the primary color constants
	 ****************************************************************************************/
	void initColors();
}
