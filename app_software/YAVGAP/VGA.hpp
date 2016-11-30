#ifndef VGA_HPP
#define VGA_HPP

#include "Traits.hpp"

class VGA {
 public:
	static short getColor(unsigned char R, unsigned char G, unsigned char B);
	static void text(int x, int y, char* text_ptr);
	static void textClearLine(int n);
	static void textClear();
	static void drawPixel(int x, int y, short pixel_color);
	static void drawLine(int x1, int y1, int x2, int y2, short pixel_color);
	static void drawFilledRect(int x1, int y1, int x2, int y2, short pixel_color);
	static void drawRect(int x1, int y1, int x2, int y2, short pixel_color);
	static void drawCircle(int xc, int yc, int radius, short pixel_color);
	static void drawFilledCircle (int xc, int yc, int radius, short pixel_color);
	static void clearScreen();

	static const int SCREEN_WIDTH;
	static const int SCREEN_HEIGHT;
};

#endif
