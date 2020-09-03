#ifndef _GRAPHICS_H
#define _GRAPHICS_H


typedef struct __window{
	char *win_buff_ptr;
	uint16_t height;
	uint16_t width;
	uint16_t y_beg;
	uint16_t x_beg;
	uint16_t curs;
}Window;


Window* newwin(uint16_t, uint16_t, uint16_t, uint16_t);
void wrefresh(Window*);

#endif
