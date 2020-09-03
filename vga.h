#ifndef _VGA_H
#define _VGA_H

#define H_PIXELS	206
#define H_COLS		103
#define VISIBLE_COLS	100
#define V_LINES		150
#define VGA_BUFF_SIZE	(H_PIXELS * V_LINES / 2)


extern char vga_buff[V_LINES][H_COLS];
void initscr(void);
void test_colors(void);

#endif
