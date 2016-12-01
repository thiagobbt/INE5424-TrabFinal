#include "pointers.hpp"
#include "VGA.hpp"

short VGA::getColor(unsigned char R, unsigned char G, unsigned char B) {
	return ((R * 31 / 255) << 11) |
		   ((G * 63 / 255) << 5) |
		   ((B * 31 / 254));
}

void VGA::text(int x, int y, char* text_ptr) {
	// assume that the text string fits on one line
	int offset = (y << 7) + x;
	while (*(text_ptr)) {
		*(ptr::character_buffer + offset) = *(text_ptr);	// write to the character buffer
		++text_ptr;
		++offset;
	}
}

void VGA::textClearLine(int n) {
	char* nothing = "                                                                                \0";
	text(0, n, nothing);
}

void VGA::textClear() {
	for (int i = 0; i < 60; ++i) {
		textClearLine(i);
	}
}

void VGA::drawPixel(int x, int y, short pixel_color) {
	int offset = (y << 9) + x;
	*(ptr::pixel_buffer + offset) = pixel_color;
}

void VGA::drawLine(int x1, int y1, int x2, int y2, short pixel_color) {
	float dx = x2 - x1;
	float dy = y2 - y1;

	int x, y;

	if (dx == 0) {
		y = y1;
		while (y <= y2) {
			drawPixel(x1, y, pixel_color);
			y++;
		}
		return;
	}

	float error = 0;
	float ratio = dy/dx;
	float derror = ratio > 0 ? ratio : -ratio;

	if (dx < 0) {
		int aux = x1;
		x1 = x2;
		x2 = aux;

		aux = y1;
		y1 = y2;
		y2 = aux;
	}

	y = y1;
	for (x = x1; x < x2; x++) {
		drawPixel(x, y, pixel_color);
		error += derror;

		if (error > 0) {
			y++;
			error--;
		}
	}
}

void VGA::drawFilledRect(int x1, int y1, int x2, int y2, short pixel_color) {
	int row, col;
	// assume that the box coordinates are valid
	for (row = y1; row <= y2; row++) {
		for (col = x1; col <= x2; col++) {
			drawPixel(col, row, pixel_color);
		}
	}
}

void VGA::drawRect(int x1, int y1, int x2, int y2, short pixel_color) {
	drawLine(x1, y1, x2, y1, pixel_color);
	drawLine(x2, y1, x2, y2, pixel_color);
	drawLine(x1, y2, x2, y2, pixel_color);
	drawLine(x1, y1, x1, y2, pixel_color);
}

void VGA::drawCircle(int xc, int yc, int radius, short pixel_color) {
	int x = radius;
	int y = 0;
	int err = 0;

	while (x >= y) {
		drawPixel(xc + x, yc + y, pixel_color);
		drawPixel(xc + y, yc + x, pixel_color);
		drawPixel(xc - y, yc + x, pixel_color);
		drawPixel(xc - x, yc + y, pixel_color);
		drawPixel(xc - x, yc - y, pixel_color);
		drawPixel(xc - y, yc - x, pixel_color);
		drawPixel(xc + y, yc - x, pixel_color);
		drawPixel(xc + x, yc - y, pixel_color);
		y++;
		err += 1 + 2 * y;
		if (2 * (err - x) + 1 > 0) {
			x--;
			err += 1 - 2 * x;
		}
	}
}

void VGA::drawFilledCircle(int xc, int yc, int radius, short pixel_color) {
	int y, x;
	for (y = -radius; y <= radius; y++) {
		for (x = -radius; x <= radius; x++) {
			if ((x * x) + (y * y) <= (radius * radius)) {
				drawPixel(x + xc, y + yc, pixel_color);
			}
		}
	}
}

void VGA::clearScreen() {
	textClear();
	drawFilledRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x00);
}
