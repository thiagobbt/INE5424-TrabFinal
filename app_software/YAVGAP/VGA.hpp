#ifndef VGA_HPP
#define VGA_HPP

#include "Traits.hpp"

namespace VGA {
	short getColor(unsigned char R, unsigned char G, unsigned char B);
	void text(int x, int y, char* text_ptr);
	void textClearLine(int n);
	void textClear();
	void drawPixel(int x, int y, short pixel_color);
	void drawLine(int x1, int y1, int x2, int y2, short pixel_color);
	void drawFilledRect(int x1, int y1, int x2, int y2, short pixel_color);
	void drawRect(int x1, int y1, int x2, int y2, short pixel_color);
	void drawCircle(int xc, int yc, int radius, short pixel_color);
	void drawFilledCircle (int xc, int yc, int radius, short pixel_color);
	void clearScreen();

	const int SCREEN_WIDTH = 319;
	const int SCREEN_HEIGHT = 239;
};

#endif
