#include "shape.h"
#include "game.h"
#include "Block.h"
#include "Board.h"

void main()
{
	srand(time(nullptr));
	Board board1(10, 0, 1), board2(40, 0, 2);
	Shape shape1(board1), shape2(board2);
	Game game(board1, board2, shape1, shape2);

	game.openMenu();
}