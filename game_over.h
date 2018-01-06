#ifndef GAME_OVER_H
	#define GAME_OVER_H
	#include "board_struct.h"
	#include <stdbool.h>

	bool is_game_over(Board* board);
	bool win(Board* board);
#endif
