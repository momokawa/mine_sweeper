mine_sweeper.out: main.o board.o input_validity.o play.o game_over.o
	gcc -g -Wall -Werror -o mine_sweeper.out play.o board.o input_validity.o game_over.o main.o

board.o: board.c board.h 
	gcc -g -Wall -Werror -c board.c

input_validity.o: input_validity.c input_validity.h
	gcc -g -Wall -Werror -c input_validity.c

play.o: play.c play.h game_over.h
	gcc -g -Wall -Werror -c play.c

game_over.o: game_over.c game_over.h
	gcc -g -Wall -Werror -c game_over.c

main.o: main.c board.h input_validity.h
	gcc -g -Wall -Werror -c main.c

clean:
	rm -fr *.o *.out
