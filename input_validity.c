// this file is for checking input validity

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#include "input_validity.h"
#include "board_struct.h"

/*
functions below are for cheking if input arguments for board setting is valid
*/

// check valid inputs for seting for board
bool is_valid_arguments_board(int argc, char* argv[]) {
	return (is_enough_input(argc, 5)) && (is_all_arg_number(argc, argv));
}

// check if there is enough input argument
bool is_enough_input( int argc, int num_desired_input ) {
	
	if ( argc > num_desired_input ) { // if argc is larger than the desired length
		printf("Too many arguments. Usage:\n./mine_sweeper.out num_rows num_cols num_mines [seed])\n");
		exit(0); // teminate program
	}
	else if ( argc < num_desired_input ) { // if argc is smaller than the desired length
		printf("Not enough arguments. Usage:\n./mine_sweeper.out num_rows num_cols num_mines [seed])\n");
		exit(0); // terminate program
	}
	else { // if it is enough inputs
		return true;
	}

}
// check if input argumets are numbers
bool is_all_arg_number(int argc, char* argv[]) {
	int i;
	for ( i = 1; i < argc; i++ ) {
		if ( !isnumber(argv[i]) ) {
			printf("Invalid input format. Input number\n");
			exit(-1); // teminate program
			return false;
		}
	}
	return true; // if all inputs are numbers
}

// check if input stirng is number
bool isnumber(char* string) {
	int i = 0;
	for ( i = 0; string[i] != '\0'; i++ ) {
		if (!isdigit(string[i]) ) { // if there is non-number char
			return false;
		}
	}
	return true;
}	




////////////////////////////////////////////////////////

/*
function belows are for checking inputs are valid when selecting tile and choosing action
*/


// this function ckecks if user selection is valid
bool is_valid_action_selection_input(int numArgsRead, int selection, int numArgsNeeded, int max_selection) {
	return isValidFormat(numArgsRead, numArgsNeeded) && selectionConstraintMet(selection, max_selection);
}

// this function return if input row and col are valid
bool is_valid_row_col_input(int numArgsRead, int numArgsNeeded, int row, int col, Board* board) {
	return isValidFormat(numArgsRead, numArgsNeeded) && intConstraintMet(row, col, board);
}

// check inputs are valid format
bool isValidFormat(int numArgsRead, int numArgsNeeded) {
	bool isValid = ( numArgsRead == numArgsNeeded);
	char lastChar;

	do {
		scanf("%c", &lastChar); // continue to read after reading two int
		if(!isspace(lastChar)) { // if there is something continued
			isValid = false;
		}
	} while ( lastChar != '\n' ); // when reaching '\n', end up checking

	return isValid;
}

/*
points to check are like below
1. whether row, col are within num_row, and num_col
2. whether tile[row][col] is concealed without being marked or questioned
*/
bool intConstraintMet(int row, int col, Board* board) {
	
	if ( (row > (*board).num_rows -1)  || row < 0 ) { // if row is out of range of board
		return false; // return invalid
	}
	else if ( (col > (*board).num_cols -1) || col < 0 ) { // if col is out of range of board
		return false; // return isvalid
	}
	else if ( ( !(*board).tiles[row][col].isQuestion ) && !(*board).tiles[row][col].isMarked ) { // the tile is not marked
	   // and questioned
		// if the tile is not marked and questioned
		if ( !(*board).tiles[row][col].isConcealed ) { // and it is revealed
			printf("This tile is already revealed.\n");
			return false;
		}
	}	

	return true; // otherwise, return true
}

/*
checks if user selection is not out of renge of all possible selection
*/
bool selectionConstraintMet(int selection, int max_selection) {
	if ( (selection < max_selection) && (selection >= 0) ) {
		return true;
	}
	else {
		return false;
	}
}
