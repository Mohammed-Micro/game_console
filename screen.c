#include <stdint.h>
#include "vga.h"
#include "graphics.h"
#include "pieces.h"
#include "screen.h"

#define TITLE_COLS 43

const enum Colors color_map[PCOLORS] = {
        COLOR_BLACK,
        COLOR_RED,
        COLOR_GREEN,
        COLOR_BLUE,
        COLOR_CYAN,
        COLOR_YELLOW,
        COLOR_MAGENTA
};

const char TITLE[] =
	"111111  222222  333333  4444444  55  666666\n"
        "111111  222222  333333  4444444  55  666666\n"
        "  11    22        33    44   44  55  66    \n"
	"  11    22        33    44   44  55  66    \n"
        "  11    22222     33    444444   55  666666\n"
	"  11    22222     33    444444   55  666666\n"
        "  11    22        33    44   44  55      66\n"
	"  11    22        33    44   44  55      66\n"
        "  11    222222    33    44    44 55  666666\n"
	"  11    222222    33    44    44 55  666666\n";

void show_new_piece(Window* win, Piece* p){

	piece_t *piece_arr = tetris[p->piece][p->rotation];
	
	//start location relative to the Window
	p->y_start = 2;
	//p->x_start = (win->width - PCOLS) / 2 ;
	

	for(uint16_t i = 0; i < PROWS; i++){
		wmove(win, p->y_start + i, p->x_start);
		for(uint16_t j = 0; j < PCOLS; j++){
			wwrite_pixel(win, color_map[(*(piece_arr + i))[j]]);
		}
	}
}

void rem_piece(Window* win, Piece* p){

	piece_t *piece_arr = tetris[p->piece][p->rotation];
	
	//start location relative to the Window
	p->y_start = 2;
	//p->x_start = (win->width - PCOLS) / 2 ;
	

	for(uint16_t i = 0; i < PROWS; i++){
		wmove(win, p->y_start + i, p->x_start);
		for(uint16_t j = 0; j < PCOLS; j++){
			wwrite_pixel(win, COLOR_BLACK);
		}
	}
}

void move_piece_down(Window *win, Piece *p){

	uint16_t py_end = p->y_start + PROWS - 1; //position of the last row in the piece to be moved

	uint16_t new_row, old_row;
	uint16_t col;

	piece_t *piece_arr = tetris[p->piece][p->rotation];

	for(uint16_t i = 0; i < PROWS; i++){
		new_row = win->width * (py_end - i + 1);
		old_row = new_row - win->width;

		for(uint16_t j = 0; j < PCOLS; j++){
			if((*(piece_arr + PROWS - i - 1))[j] > COLOR_BLACK){
				col = p->x_start + j;
				win->win_buff[new_row + col] = win->win_buff[old_row + col];
				win->win_buff[old_row + col] = COLOR_BLACK;
			}
		}
	}

	++p->y_start;

}

void move_piece_right(Window* win, Piece *p){

	/* 01100 0000
	 * 01100 0000
	 * 00100 0000
	 */

// 	uint16_t px_end = p->x_start + PCOLS - 1;

// 	piece_t *piece_arr = tetris[p->piece][p->rotation];

// 	uint16_t row;

// 	for(uint16_t i = 0; i < PROWS; i++){
		
// 		row = (p->y_start + i) * win->width;
// 		for(uint16_t j = 1; j <= PCOLS; j++){
			
// 			if( (*(piece_arr + i))[PCOLS - j] > COLOR_BLACK){
// 				win->win_buff[row + px_end - j + 1] =
// 					color_map[(*(piece_arr + i))[PCOLS - j]];
// 				win->win_buff[row + px_end - j] = COLOR_BLACK;
// 			}
// 		}
// 	}

// 	++p->x_start;
	rem_piece(win,p);
	++p->x_start;
	show_new_piece(win,p);
}

void move_piece_left(Window* win, Piece *p){

	/* 0000 01100
	 * 0000 01100
	 * 0000 00100
	 */

	piece_t *piece_arr = tetris[p->piece][p->rotation];
	
	uint16_t row;

	for(uint16_t i = 0; i < PROWS; i++){
		
		row = (p->y_start + i) * win->width;
		for(uint16_t j = 0; j < PCOLS; j++){

			if( (*(piece_arr + i))[j] > COLOR_BLACK){
				win->win_buff[row + p->x_start + j - 1]=
					color_map[(*(piece_arr + i))[j]];
				win->win_buff[row + p->x_start + j] = COLOR_BLACK;
			}
		}
	}

	--p->x_start;
}

void rotate_piece(Window *win, Piece *p){

	piece_t *piece_arr = tetris[p->piece][p->rotation];

	uint16_t i,j;
	uint16_t win_row;

	for(i = 0; i < PROWS; i++){
		win_row = (p->y_start + i) * win->width;

		for(j = 0; j < PCOLS; j++){
			if((*(piece_arr + i))[j] > COLOR_BLACK){
				win->win_buff[win_row + p->x_start + j] = COLOR_BLACK;
			}
		}
	}
	
	if(++p->rotation == 2){
		p->rotation = ROTATION_NORMAL;
	}

	piece_arr = tetris[p->piece][p->rotation];

	for(i = 0; i < PROWS; i++){
		win_row = (p->y_start + i) * win->width;

		for(j = 0; j < PCOLS; j++){
			if((*(piece_arr + i))[j] > COLOR_BLACK){
				win->win_buff[win_row + p->x_start + j] = color_map[(*(piece_arr + i))[j]];
			}
		}
	}
}

int8_t try_move_down(Window *win, Piece *p){

        uint16_t i, j;
        piece_t *piece_arr = tetris[p->piece][p->rotation];
        uint16_t win_row;

        for(i = 0; i < PROWS - 1; i++){
                win_row = (p->y_start + i + 1) * win->width;
                for(j = 0; j < PCOLS; j++){
                        if((*(piece_arr + i))[j] > COLOR_BLACK){
                                if((*(piece_arr + i + 1))[j] == COLOR_BLACK && win->win_buff[win_row + p->x_start + j] > COLOR_BLACK){
                                        return -1;
                                }
                        }
                }
        }

// 	uint16_t border;
// 	wgetmaxyx(win, &border, 0);
// 	win_row = (p->y_start + i + 1) * win->width;

//         for(j = 0; j < PCOLS; j++){
//                 if((*(piece_arr + i))[j] > COLOR_BLACK){
//                         if(p->y_start + i + 1 >= border || win->win_buff[win_row + p->x_start + j] > COLOR_BLACK){
// 				return -1;
// 			}
//                 }

//         }
//	if (p->y_start + PROWS >= win->height) return -1;
	win_row = (p->y_start + PROWS) * win->width;
	for (j = 0; j < PCOLS; j ++)
		if (*(piece_arr+PROWS-1)[j]!=COLOR_BLACK
		    && win->win_buff[win_row + p->x_start + j] != COLOR_BLACK)
			return -1;
        move_piece_down(win, p);
        return 0;
}

int8_t try_move_right(Window *win, Piece *p){

	piece_t *piece_arr = tetris[p->piece][p->rotation];
	uint16_t i, j;
	uint16_t win_row;

	for(i = 0; i < PROWS; i++){
		win_row = (p->y_start + i) * win->width;
		for(j = 0; j < PCOLS - 1; j++){

			if((*(piece_arr + i))[j] > COLOR_BLACK){
				if((*(piece_arr + i))[j + 1] == COLOR_BLACK && win->win_buff[win_row + p->x_start + j + 1] > 
						COLOR_BLACK){
					return -1;
				}
			}
		}
	}

	/*
	j = PCOLS - 1;
	for(i = 0; i < PROWS; i++){
		win_row = (p->y_start + i) * win->width;
		if(win->win_buff[win_row + p->x_start + j] > COLOR_BLACK){
			if(win->win_buff[win_row + p->x_start + j + 1] > COLOR_BLACK){
			}
		}
	}
	*/
//	if (p->x_start + PCOLS >= win->width) return -1;
	win_row = p->y_start * win->width;
	for (i = 0; i < PROWS; i ++ && win_row += win_width)
		if (*(piece_arr+i)[PCOLS-1]!=COLOR_BLACK
		    && win->win_buff[win_row + p->x_start + PCOLS] != COLOR_BLACK)
			return -1;
        move_piece_down(win, p);
        return 0;
}

int8_t try_move_left(Window *win, Piece *p){

	piece_t *piece_arr = tetris[p->piece][p->rotation];

	uint16_t i, j;
	uint16_t win_row;
	uint16_t px_end = p->x_start + PCOLS - 1;

	for(i = 0; i < PROWS; i++){
		win_row = (p->y_start + i) * win->width;
		for(j = 0; j < PCOLS - 1; j++){
			if((*(piece_arr + i))[PCOLS - j - 1] > COLOR_BLACK){
				if((*(piece_arr + i))[PCOLS - j - 2] == COLOR_BLACK && win->win_buff[win_row + px_end - j - 1] >
						COLOR_BLACK){
					return -1;
				}
			}
		}
	}

//	if (p->x_start == 0) return -1;
	win_row = p->y_start * win->width;
	for (i = 0; i < PROWS; i ++ && win_row += win_width)
		if (*(piece_arr+i)[0]!=COLOR_BLACK
		    &&(win_row + p->x_start < 1 || win->win_buff[win_row + p->x_start + -1] != COLOR_BLACK))
			return -1;

	move_piece_left(win, p);
	return 0;
}

void show_title(void){

	uint16_t vga_col = (H_COLS - TITLE_COLS) / 2;

	uint16_t i = 0, vga_row = 5;

	while(TITLE[i]){

		if(TITLE[i] == '\n'){
			vga_col = (H_COLS - TITLE_COLS) / 2;
			vga_row++;
		}
		else if(TITLE[i] == ' '){
			vga_buff[vga_row][vga_col++] = COLOR_BLACK;
		}
		else{
			vga_buff[vga_row][vga_col++] = color_map[TITLE[i] - '0'];
		}
		i++;
	}
}

