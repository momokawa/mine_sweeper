// this header file is for palying

#ifndef PLAY_H
	#define PLAY_H
	#include "board_struct.h"
	void play(Board* board);
	void PrintResult(Board* board);
	void _play(Board* board);
	void SelectTile(Board* board, int* row, int* col);
	void AddAction(Board* board, int row, int col);
	void action_to_question_tile(Board* board, int row, int col);
	void action_to_marked_tile(Board* board, int row, int col);
	void action_to_concealed_tile(Board* board, int row, int col);
	void action_to_no_mine_tile(Board* board, int row, int col);
	void PrintCurrentBoard(Board* board);
	void PrintLastBoard(Board* board);
#endif
