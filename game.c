#include "game.h"

const uint8_t BORDER_THICKNESS = 1;

static Piece cur_piece;
static Piece next_piece;
static Window main_board;

void init_game(void){

	show_title();
	
	main_board = newwin(100, 30, 30, 35);
	box(&main_board, COLOR_WHITE, BORDER_THICKNESS);
	
	wrefresh(&main_board);
}

void new_game(void){

	cur_piece = get_rand_piece();
	next_piece = get_rand_piece();

	show_new_piece(&main_board, &cur_piece);
	wrefresh(&main_board);
}

void main_loop(void){

	uint32_t delay = 0;
	while(1){
		delay += 10;
		switch(serial_read_byte()){
			case 's':
				try_move_down(&main_board, &cur_piece);
				wrefresh(&main_board);
				break;
			case 'a':
				try_move_left(&main_board, &cur_piece);
				wrefresh(&main_board);
				break;
			case 'd':
				try_move_right(&main_board, &cur_piece);
				wrefresh(&main_board);
				break;
			case 'w':
				rotate_piece(&main_board, &cur_piece);
				wrefresh(&main_board);
				break;
			case 'p':
				while(serial_read_byte != 'p');
				break;
		}

		if(delay == 1000000){
			if(try_move_down(&main_board, &cur_piece) < 0){
				rem_complete_rows_cols(&main_board);
				cur_piece = next_piece;
				next_piece = get_rand_piece();
				show_new_piece(&main_board, &cur_piece);
			}
			wrefresh(&main_board);
			delay = 0;
		}
	}
}

void start_game(void){

	init_game();
	new_game();
	main_loop();
}


