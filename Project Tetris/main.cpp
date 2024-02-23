#include "shape.h"
#include "game.h"
#include "block.h"
#include "board.h"
#include "bot.h"
#include "human.h"

void main()
{
	srand(time(nullptr));
	Board board1(10, 0), board2(40, 0);
	Game game(board1, board2);
	
	game.openMenu();
}