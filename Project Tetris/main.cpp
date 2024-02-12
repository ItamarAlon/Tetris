#include "shape.h"
#include "game.h"
#include "block.h"
#include "board.h"
#include "computer.h"

void main()
{
	srand(time(nullptr));
	Board board1(10, 0, 1), board2(40, 0, 2);
	Computer shape1(board1), shape2(board2);
	Game game(board1, board2, shape1, shape2);
	
	game.openMenu();

	//srand(time(nullptr));
	//Board board(10, 0, 1);
	//Computer AI(board);
	////Game game(board1, board2, shape1, shape2);

	////board.setFreeSpaceValue(-2, 5, 17);
	////board.setFreeSpaceValue(-2, 5, 18);
	//board.print();
	//Position best;
	//ShowConsoleCursor(false);
	//while (true)
	//{
	//	best.score = -999999;
	//	AI.findBestPosition(best);
	//	AI.moveToPosition(best);
	//	Sleep(10);
	//	AI.setShape();
	//}

	//gotoxy(0, board.getHeight() + 2);

}