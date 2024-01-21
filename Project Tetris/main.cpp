#include "shape.h"
#include "game.h"
#include "Block.h"
#include "Board.h"

#include "Libraries.h"

void main()
{
	srand(time(nullptr));
	Board board;
	Shape s(board);
	Game game(board, s);


	//game.runGame();

	game.printMenu();
}