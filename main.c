 // This file is for main file to play mine sweeper

#include <stdio.h>
#include <stdlib.h>

#include "play.h"
#include "board.h"

int main(int argc, char* argv[]) {
	Board board;
	GenerateBoard(argc, argv, &board); // initilize board with use input argument
	play(&board);
	FreeBoard(&board); // delete location
	return 0;
}
