#ifndef BOARD_STRUCT_H
	#define BOARD_STRUCT_H
	// struct for each tile
	#include <stdbool.h>
	typedef struct Tile_struct{
		bool isConcealed; // is this tile concealed? 
		bool isMine; // default setting of isMine is false
		bool isQuestion; // is this tile questioned?
		bool isMarked; // is this tile marked?
		int num_mine_around_tile; // how many mines around tile
	} Tile;

	// struct for board
	typedef struct Board_struct{
		Tile** tiles;
		bool is_loss;
		int num_rows;
		int num_cols;
		int num_mines;
		int num_mines_left;
		int seed; // val for generating randam number
	} Board;
#endif
