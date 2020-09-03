#ifndef _GRAPHICS_H
#define _GRAPHICS_H

typedef unsigned short int uint16_t;
typedef unsigned char uint8_t;

enum Colors{
	COLOR_BLACK = 0X00,
	COLOR_RED = 0X1,
	COLOR_GREEN = 0X02,
	COLOR_BLUE = 0X08,
	COLOR_YELLOW = 0X03,	//RED AND GREEN
	COLOR_CYAN = 0X0A,	//GREEN AND BLUE
	COLOR_MAGENTA = 0X09,	//RED AND BLUE
	COLOR_WHITE = 0X0F	//RED, GREEN AND BLUE
};

typedef struct __window{
	char *win_buff;
	uint16_t height;
	uint16_t width;
	uint16_t y_beg;
	uint16_t x_beg;
	uint16_t curs;
}Window;


Window newwin(uint16_t, uint16_t, uint16_t, uint16_t);
void wrefresh(Window*);
void box(Window*, uint8_t, uint8_t);

#endif
