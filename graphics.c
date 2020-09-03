#include "graphics.h"
#include "vga.h"

Window* newwin(uint16_t height, uint16_t width, uint16_t y_beg, uint16_t x_beg){

	Window *win  = {
		.win_buff_ptr = (char*) malloc(height * width),
		.height = height,
		.width = width,
		.y_beg = y_beg,
		.x_beg = x_beg,
		.curs = 0
	};

	return win;
}

void wrefresh(Window *win){

	while(!in_backporch());

	uint16_t y_end = y_beg + win->height;
	uint16_t x_end = x_beg + win->width;
	uint16_t cnt = 0;

	for(uint16_t i = win->y_beg; i < y_end; i++){
		
		for(uint16_t j = win->x_beg; j < x_end; j++){

			vga_buff[i][j] = win->win_buff_ptr[cnt++];
		}
	}
}
