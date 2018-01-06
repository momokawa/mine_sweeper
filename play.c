/*
this file allow program to play with minesweeper
*/

#include <stdio.h>
#include <stdlib.h>
#include "play.h"
#include "board_struct.h"
#include "input_validity.h"
#include "game_over.h"

// play game
void play(Board* board) {

	// repeat until it is not game over
	do {
		printf("There are %d mines left\n", (*board).num_mines_left); // print num of mine left in board
		PrintCurrentBoard(board); // print current state of board
		_play(board);
	} while(!is_game_over(board));

	
	// after game over
	// print last board with win or lose
	PrintLastBoard(board);
	PrintResult(board);

	return;
}

// this function prints result
void PrintResult(Board* board) {

	if ( (*board).is_loss ) {
		printf("You Lost :(\n");
	}
	else if ( win(board) ) {
		printf("You Won!!\n");
	}
	return;
}

void _play(Board* board) {
	int row, col;
	SelectTile(board, &row, &col);
	AddAction(board, row, col);
	return;
}
// select tile to open
void SelectTile(Board* board, int* row, int* col) {
	int numArgsRead;

	 do{
	 	printf("Enter row a row between 0-%d and a column between 0-%d: ", (*board).num_rows-1, (*board).num_cols-1);
		numArgsRead = scanf("%d %d", row, col); // get input

	 }while (!is_valid_row_col_input(numArgsRead, 2, *row, *col, board)); // check if the inputs are valid

	 return;
}

// add action to the tile
void AddAction(Board* board, int row, int col) {

	// select action to do 
	if ( (*board).tiles[row][col].isMarked ) { // action if the tile is marked
		action_to_marked_tile(board, row, col);	
	}
	else if ( (*board).tiles[row][col].isQuestion ) {// action if the tile is questioned
		action_to_question_tile(board, row, col);	
	}	
	else if ( (*board).tiles[row][col].isConcealed ) { // action if the tile is concealed 
		// reveal the tile and show the number of mines around it
		action_to_concealed_tile(board, row, col);
	}
	return;
}

// function to add action when the tile is questioned
void action_to_question_tile(Board* board, int row, int col) {
	int selection;
	int numArgsRead;
	
	// get user selection
	printf("Enter Action\n");
	printf("0. UnQuestion\n1. Cancel\n");
	printf("Action: ");
	numArgsRead = scanf("%d", &selection); 

	if (!is_valid_action_selection_input(numArgsRead, selection, 1, 1) ) { // if this input is invalid, go back to row, col selection
		_play(board); // go back to the selection of row, col
	}

	// add action
	if ( selection == 0 ) { // make the tile concealed
		(*board).tiles[row][col].isQuestion = false;
		(*board).tiles[row][col].isConcealed = true;
	}
	else if ( selection == 1 ) {
		return; // do nothing
	}
	return;
}

// function to add action when the tile is marked
void action_to_marked_tile(Board* board, int row, int col) {
	int selection;
	int numArgsRead;
	
	// get user selection
	printf("Enter Action\n");
	printf("0. UnMark\n1. Cancel\n");
	printf("Action: ");
	numArgsRead = scanf("%d", &selection);

	if ( !is_valid_action_selection_input(numArgsRead, selection, 1, 1) ) { // if this input is invalid, go back to row, col selection
		_play(board);
	}

	// add action
	if ( selection == 0 ) { // make the tile concealed again
		(*board).tiles[row][col].isMarked = false;
		(*board).tiles[row][col].isConcealed = true;
		(*board).num_mines_left++; // increase num_mines_left
	}
	else if ( selection == 1 ) {
		return; // do nothing
	}
	return;
}

// FIXME add recursion
// function to add action when the tile is unconcealed
void action_to_concealed_tile(Board* board, int row, int col) {
	int selection;
	int numArgsRead;

	// get user selection
	printf("Enter Action\n");
	printf("0. Reveal\n1. Question\n2. Mark\n3. Cancel\n");
	printf("Action: ");

	numArgsRead = scanf("%d", &selection);
	if ( !is_valid_action_selection_input(numArgsRead, selection, 1, 3) ) {
		// if this input is invalid, go back to row, col selection
		_play(board);
	}

	if ( selection == 0 ) { // reveal
		if ( (*board).tiles[row][col].isMine ) { // if user chooses mine // BASE CASE !
			(*board).tiles[row][col].isConcealed = false; // reveal
			(*board).is_loss = true; // use loses
		}
		else if ( (*board).tiles[row][col].num_mine_around_tile != 0 ) { // it the tile does have mines around it
			// BASE CASE 2
			(*board).tiles[row][col].isConcealed = false; // reveal
			return; // do thing
		}
		else { // if num_mine_around_tile is 0, look into tiles around it
			(*board).tiles[row][col].isConcealed = false; // reveal
			action_to_no_mine_tile(board, row, col);
		}
		// if num_mines_around_tile is 0, look into tiles around the tile
	}
	else if ( selection == 1 ) { // question
		(*board).tiles[row][col].isQuestion = true;
	}
	else if ( selection  == 2) { // mark
		(*board).tiles[row][col].isMarked = true;
		(*board).num_mines_left--; // reduce the numver of mines_left
	}
	else if ( selection  == 3 ) {
		// do nothing
	}
	return;

}

// this function defines action when revealing the tile with num_mines_around_tile is 0
// ( so the case it is used, there is no mine around the tiles[row][col] )
void action_to_no_mine_tile(Board* board, int row, int col) {
	int i,k;


	for ( i = -1; i< 2; i++ ) {
		for ( k = -1; k < 2; k++ ) {
			// look into tiles around it
			// avoid the tile itself and tiles out of range
			if ( !(( i == 0 ) && ( k == 0) ) // when not being the tile itself
				&& ( (row + i ) >= 0 ) // make it inside the board
				&& ( (col + k ) >= 0 )
				&& ( (row + i ) < (*board).num_rows )
				&& ( (col + k ) < (*board).num_cols ) )  {
					if (  (*board).tiles[row+i][col+k].num_mine_around_tile != 0 ) { // BASE CASE
						(*board).tiles[row+i][col+k].isConcealed = false; // reveal it
						// go to another tile	
					}
					else { // repeat whne the tile has not mines around it
						// recursion
						if ( !(*board).tiles[row+i][col+k].isConcealed ) { // if it is already revealed
							 // do nothing, go to another tile
						}
						else {
							(*board).tiles[row+i][col+k].isConcealed = false; // reveal
							action_to_no_mine_tile(board, row+i, col+k);
						}
					}
				}
		}
	}
	return;
}

// this function prints current status of board
void PrintCurrentBoard(Board* board) {
	char charStatus[4] = {'#', '?', '!'};
	int row, col;
	char tempStatus;

	// print status of board with row num
	for ( row = (*board).num_rows - 1 ; row >= 0; row-- ) {
		printf("%d ", row ); // print row number 
		for ( col = 0; col < (*board).num_cols; col++ ) {
			if ( (*board).tiles[row][col].isQuestion ) { // if the tile marked as question
				tempStatus = charStatus[1];
				printf("%c", tempStatus); // print status
			}
			else if ( (*board).tiles[row][col].isMarked  ) { // if the tile is marked
				tempStatus = charStatus[2];
				printf("%c", tempStatus); // print status
			}
			else if ( (*board).tiles[row][col].isConcealed  ) { // if the tile has not yet been revealed
				tempStatus = charStatus[0];
				printf("%c", tempStatus); // print status
			}
			else { // if the tile is revealed
				printf("%d", (*board).tiles[row][col].num_mine_around_tile ); //  show  the number of mine around it
			}
			
			if ( col != (*board).num_cols - 1 ) {	// if it is not the end of the row
				printf(" "); // add space
			}
			else { // if it is the end
				printf("\n"); // add enter
			}
		}
	}
	
	// print col num
	printf("  ");
	for ( col = 0; col < (*board).num_cols; col++ ) {
		printf("%d", col);
		if ( col != (*board).num_cols -1 ) { // if it is not the end of row
			printf(" "); // add space
		}
		else { // if it is the end of row
			printf("\n");
		}
	}
}

// this function prints mines and the number of mines around the tile
void PrintLastBoard(Board* board) {
	char mine = '*';
	int row, col;
	
	// print status of board with row num
	for ( row = (*board).num_rows - 1 ; row >= 0; row-- ) {
		printf("%d ", row ); // print row number 
		for ( col = 0; col < (*board).num_cols; col++ ) {
			// print contents
			if ( (*board).tiles[row][col].isMine  ) { // if the tile has not yet been revealed
				printf("%c", mine); 
			}
			else { // otherwise, print the number of mines around the tile
				printf("%d", (*board).tiles[row][col].num_mine_around_tile);
			}
			
			if ( col != (*board).num_cols - 1 ) {	// if it is not the end of the row
				printf(" "); // add space
			}
			else { // if it is the end
				printf("\n"); // add enter
			}
		}
	}
	
	// print col num
	printf("  ");
	for ( col = 0; col < (*board).num_cols; col++ ) {
		printf("%d", col);
		if ( col != (*board).num_cols -1 ) { // if it is not the end of row
			printf(" "); // add space
		}
		else { // if it is the end of row
			printf("\n");
		}
	}
}


