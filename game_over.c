#include <stdio.h>
#include <stdbool.h>

#include "game_over.h"

/* 
check if it is game over
two pattern for game over
1. user lose ( choose tile with mine)
2. user win ( fill in all blanks )
 */
bool is_game_over(Board* board) {
	return (*board).is_loss || win(board); 
}

/*
The condition to win 
1. all mines are marked
2. all non-mines are revealed
*/
bool win(Board* board) {
	int row, col;
	if ( (*board).num_mines_left != 0 ) { // if there is still unmarked mine
		return false;
	}
	else { // if there is no unmarked mine
		for ( row = 0; row < (*board).num_rows ; row++ ) {
			for ( col = 0; col < (*board).num_cols; col++ ) {
				if ( (*board).tiles[row][col].isConcealed && !(*board).tiles[row][col].isMarked) {
					// if there is at least one concealed tile, which is not isMarked
					return false;
				}
				else if ( (*board).tiles[row][col].isQuestion ) {
					return false; // if there is questioned tile, return false;
				}
			}
		}
	}
	return true; // otherwise, retur true;
}

