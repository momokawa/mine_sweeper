#ifndef INPUT_VALIDITY_H
	#define INPUT_VALIDITY
	#include <stdbool.h>
	#include "board_struct.h"

	// functions for checking command line arguments
	bool is_valid_arguments_board(int argc, char* argv[]);
	bool is_enough_input( int argc, int num_desired_input);
	bool is_all_arg_number(int argc, char* argv[]);
	bool isnumber(char* string);

	// fucntions for checking row and col when selecting tile to add action
	bool is_valid_action_selection_input(int numArgsRead, int selection, int numArgsNeede, int max_selection);
	bool is_valid_row_col_input(int numArgs, int numArgsNeeded, int row, int col, Board* board);
	bool isValidFormat(int numArgs, int numArgsNeeded);
	bool intConstraintMet(int row, int col, Board* board);
	bool selectionConstraintMet(int selection, int max_selection);
#endif
