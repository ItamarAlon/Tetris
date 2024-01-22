#include "shape.h"
#include "game.h"
#include "Block.h"
#include "Board.h"

#include "Libraries.h"

void main()
{
	srand(time(nullptr));
	Board board1(10, 0, 1), board2(40, 0, 2);
	Shape shape1(board1), shape2(board2);
	Game game(board1, board2, shape1, shape2);

	//int anchorX = board.X_START + board.WIDTH / 2, anchorY = board.Y_START + 1;
	//if (board1.isSpaceTaken(board1.X_START + board1.WIDTH / 2, board1.Y_START + 1))
	//	cout << "taken";
	//else
	//	cout << "not taken";
	//game.runGame();

	game.printMenu();
}