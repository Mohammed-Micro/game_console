#include "graphics.h"


Window* newwin(uint16_t height, uint16_t width, uint16_t y_beg, uint16_t x_beg){

	Window *win  = {
		.win_buff_ptr = malloc(height * width),
		.height = height,
		.width = width,
		.y_beg = y_beg,
		.x_beg = x_beg,
		.curs = 0
	};

	return win;
}
