// the following variables give the size of the pixel buffer
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern void display7seg(char values[8]);

/****************************************************************************************
 * Subroutine to move the LCD cursor
 ****************************************************************************************/
extern void LCD_cursor(int x, int y);

/****************************************************************************************
 * Subroutine to send a string of text to the LCD 
 ****************************************************************************************/
extern void LCD_text(char* text_ptr);

/****************************************************************************************
 * Subroutine to turn off the LCD cursor
 ****************************************************************************************/
extern void LCD_cursor_off();

/****************************************************************************************
 * Subroutine to send a string of text to the VGA monitor 
 ****************************************************************************************/
extern void VGA_text(int x, int y, char* text_ptr);

/****************************************************************************************
 * Subroutine to clear the text buffer 
 ****************************************************************************************/
extern void VGA_text_clear();

/****************************************************************************************
 * Draw a filled rectangle on the VGA monitor 
 ****************************************************************************************/
extern void VGA_box(int x1, int y1, int x2, int y2, short pixel_color);

/****************************************************************************************
 * Subroutine to clear the screen 
 ****************************************************************************************/
extern void VGA_clear_screen();

/****************************************************************************************
 * Draw a line on the VGA monitor 
 ****************************************************************************************/
extern void VGA_draw_line(int x0, int y0, int x1, int y1, short pixel_color);

/****************************************************************************************
 * Draw a circle on the VGA monitor 
 ****************************************************************************************/
extern void VGA_draw_circle(int xc, int yc, int radius, short pixel_color);

/****************************************************************************************
 * Draw a filled circle on the VGA monitor 
 ****************************************************************************************/
extern void VGA_draw_filled_circle (int xc, int yc, int radius, short pixel_color);
