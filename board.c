// this file is for setting board and generating board

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "board.h"
#include "input_validity.h" // check input valiidity


// FreeBoard
// delete the location of board
void FreeBoard(Board* board) {
	
	int row;

	for ( row = 0; row < (*board).num_rows; row++ ) {
		free((*board).tiles[row]);
	}
	free((*board).tiles);

	return;
}

// generating board from user input and return seeds for random generatori

void  GenerateBoard(int argc, char* argv[], Board* board) {
	
	// initilzie board from user input
	// if there is invalid inputs and invalid number of arguments, stop program
	if ( is_valid_arguments_board(argc, argv) ) { // if the user input arguments are all valid
		// store these values to the board struct
		(*board).num_rows = atoi(argv[1]); // num of rows of board
		(*board).num_cols = atoi(argv[2]); // num of cols of board
		(*board).num_mines = atoi(argv[3]); // num of mines in board
		(*board).num_mines_left = (*board).num_mines; // num of mines left in board
		(*board).seed = atoi(argv[4]); // val for generating random number
		(*board).is_loss = false; // val for checking if use loses
		GenerateTiles(board); // generate tiles 2D array
		GenerateMines(board); // generate mines positions randomly
		calc_num_mines_around_tile(board); // calculate the number of mines around each tile
	}
	return;
}

// this fucntion generates number of mines around each tile
void calc_num_mines_around_tile(Board* board) {
	int row, col;
	int i, k;
	int num_mine_around_tile = 0;
	for ( row = 0; row < (*board).num_rows; row++ ) {
		for ( col = 0; col < (*board).num_cols; col++ ) { // count the number of mines aorund tiles[row][col]
			// max:8, min: 0
			num_mine_around_tile = 0;
			if ( !(*board).tiles[row][col].isMine) { // if tiles[row][col] is not mine tile
				for ( i = -1; i < 2; i++ ) {
					for ( k = -1; k < 2; k++ ) {
						/* 
							if tiles[row+i}[col+k] is not the tile itself and tiles[row+i][col+k]
							does exist
						 	calc the num
						*/
						if ( ( !((i == 0) &&  ( k == 0)) ) 
								&& ( (row+i) >=0) && ( (col+k) >= 0) 
								&& ((row+i) < (*board).num_rows)
								&& ((col+k) < (*board).num_cols)) { 
							if ( (*board).tiles[row+i][col+k].isMine ) {
								// if a tile next to the tile is mine
								num_mine_around_tile++; // count up
							}
						}

					}
				}
				(*board).tiles[row][col].num_mine_around_tile = num_mine_around_tile;
			}
		} // end of col
	} // end of row
}

// this function generate tiles from num_cols and num_rows of board
void GenerateTiles(Board* board) {
	int row;
	
	// allocate mines
	(*board).tiles = (Tile**)malloc((*board).num_rows * sizeof(Tile*));
	for ( row = 0; row < (*board).num_rows; row++ ) { // allocate for each row
		(*board).tiles[row] = (Tile*)malloc((*board).num_cols * sizeof(Tile)); 
	}

	assign_false_to_ismine(board); // assign false to all isMine as default
	assign_true_to_isconcealed(board); // assign true to all isConcealed as default
	assign_false_to_isquestion(board); // assign false to all isQuesion as default
	assign_false_to_ismarked(board); // assign false to all isMarked as default

	return;
}

// make all isMine false as default
void assign_false_to_ismine(Board* board) {
	int row, col;
	
	for ( row = 0; row < (*board).num_rows; row++ ) {
		for ( col = 0; col < (*board).num_cols; col++ ) {
			((*board).tiles[row][col]).isMine = false;
		}
	}
	return;
}

// initlize all isConcealed with true as default
// that means, at first point, all files are hidden
void assign_true_to_isconcealed(Board* board) {
	int row, col;
	
	for ( row = 0; row <(*board).num_rows; row++ ) {
		for ( col = 0; col < (*board).num_cols; col++ ) {
			((*board).tiles[row][col]).isConcealed = true;
		}
	}
	return;
}

// initlize all isQuestion with false as default
// that means, at first point, all files is not questioned
void assign_false_to_isquestion(Board* board) {
	int row, col;
	
	for ( row = 0; row <(*board).num_rows; row++ ) {
		for ( col = 0; col < (*board).num_cols; col++ ) {
			((*board).tiles[row][col]).isQuestion = false;
		}
	}
	return;
}

// initlize all isMarked with false as default
// that means, at first point, all files is not marked
void assign_false_to_ismarked(Board* board) {
	int row, col;
	
	for ( row = 0; row <(*board).num_rows; row++ ) {
		for ( col = 0; col < (*board).num_cols; col++ ) {
			((*board).tiles[row][col]).isMarked = false;
		}
	}
	return;
}
// generate mines positions randomly
void GenerateMines(Board* board) {
	int i;
	int row, col;
	int hasMine = false; // val just for repeating assign in case that it already has mine
	srand((*board).seed);

	for ( i = 1; i <= (*board).num_mines; i++ ) {
		hasMine = false;
		while ( !hasMine ) {
			row = rand() % (*board).num_rows; // generate num from 0 to num_row -1
			col = rand() % (*board).num_cols; // generate num from 0 to num_col -1
			if ( ((*board).tiles[row][col]).isMine == true ) { // if the position already has mine
				// repeat same procedure again.
				hasMine = false;
			}
			else {
				((*board).tiles[row][col]).isMine = true; // the position has mine
				// show where are mines
				printf("Placing mine at %d, %d\n", row, col);
				hasMine = true; // otherwise, add one more mine
			}
		}
	}
	return;
}
