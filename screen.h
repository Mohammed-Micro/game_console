#ifndef _SCREEN_H
#define _SCREEN_H

#include <stdint.h>
#include "vga.h"
#include "graphics.h"
#include "pieces.h"


#define PCOLORS	8

void show_new_piece(Window*, Piece*);
void move_piece_down(Window*, Piece*);
void move_piece_right(Window*, Piece*);
void move_piece_left(Window*, Piece*);
void rotate_piece_cwise(Window*, Piece*);
void rotate_piece_ccwise(Window *win, Piece *p)
int8_t try_move_down(Window*, Piece*);
int8_t try_move_right(Window*, Piece*);
void show_title(void);

#endif
