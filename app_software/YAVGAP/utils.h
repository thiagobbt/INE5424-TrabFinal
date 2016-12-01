// the following variables give the size of the pixel buffer
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern short red;
extern short green;
extern short blue;
extern short color;

extern short fill_mode;


/****************************************************************************************
 * Reverses a string
 ****************************************************************************************/
extern void reverse(char str[], int length);

/****************************************************************************************
 * Converts a number to a char*
 ****************************************************************************************/
extern char* itoa(int num, char* str, int base);

/****************************************************************************************
 * Displays hexadecimal numbers to the 7 segment displays
 ****************************************************************************************/
extern void display7seg(char values[8]);

/****************************************************************************************
 * Zeroes the 7 segment displays
 ****************************************************************************************/
extern void clear7seg();

/****************************************************************************************
 * Subroutine to move the LCD cursor
 ****************************************************************************************/
extern void LCD_cursor(int x, int y);

/****************************************************************************************
 * Subroutine to send a string of text to the LCD 
 ****************************************************************************************/
extern void LCD_text(char* text_ptr);

/****************************************************************************************
 * Subroutine to clear the LCD
 ****************************************************************************************/
extern void LCD_clear();

/****************************************************************************************
 * Subroutine to turn off the LCD cursor
 ****************************************************************************************/
extern void LCD_cursor_off();

/****************************************************************************************
 * Subroutine to convert a regular RGB color to the color expected by the VGA
 ****************************************************************************************/
extern short VGA_get_color(unsigned char R, unsigned char G, unsigned char B);

/****************************************************************************************
 * Subroutine to clear a line of text of the VGA monitor
 ****************************************************************************************/
extern void VGA_text_clear_line(int n);

/****************************************************************************************
 * Subroutine to send a string of text to the VGA monitor 
 ****************************************************************************************/
extern void VGA_text(int x, int y, char* text_ptr);

/****************************************************************************************
 * Subroutine to clear the text buffer 
 ****************************************************************************************/
extern void VGA_text_clear();

/****************************************************************************************
 * Draw a line on the VGA monitor 
 ****************************************************************************************/
extern void VGA_draw_line(int x0, int y0, int x1, int y1, short pixel_color);

/****************************************************************************************
 * Draw a filled rectangle on the VGA monitor 
 ****************************************************************************************/
extern void VGA_draw_filled_rect(int x1, int y1, int x2, int y2, short pixel_color);

/****************************************************************************************
 * Draw a rectangle on the VGA monitor
 ****************************************************************************************/
extern void VGA_draw_rect(int x1, int y1, int x2, int y2, short pixel_color);

/****************************************************************************************
 * Subroutine to clear the screen
 ****************************************************************************************/
extern void VGA_clear_screen();

/****************************************************************************************
 * Draw a circle on the VGA monitor 
 ****************************************************************************************/
extern void VGA_draw_circle(int xc, int yc, int radius, short pixel_color);

/****************************************************************************************
 * Draw a filled circle on the VGA monitor 
 ****************************************************************************************/
extern void VGA_draw_filled_circle (int xc, int yc, int radius, short pixel_color);

/****************************************************************************************
 * Initializes the primary color constants
 ****************************************************************************************/
extern void init_colors();
