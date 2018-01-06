// this header file is for defualt setting for board

#ifndef BOARD_H
	#define BOARD_H
	#include <stdbool.h>
	#include "board_struct.h"
	
	void GenerateBoard(int argc, char* argv[], Board* board);
	void FreeBoard(Board* board);
	void calc_num_mines_around_tile(Board* board);
	void GenerateTiles(Board* board);
	void assign_false_to_ismine(Board* board);
	void assign_true_to_isconcealed(Board* board);
	void assign_false_to_isquestion(Board* board);
	void assign_false_to_ismarked(Board* board);
	void GenerateMines(Board* board);
#endif
