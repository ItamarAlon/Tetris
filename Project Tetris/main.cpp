#include "shape.h"
#include "game.h"
#include "Block.h"
#include "Board.h"

#include "Libraries.h"

void main()
{
	Board board;
	////board.printFreeSpace(0,0);
	bool shapeP1 = true;
	Shape s(board);
	bool isDeleted=false;
	Game game(board, s);


	board.print();
	board.printFreeSpace();
	while (true)
	{
		shapeP1 = s.moveShapeDown();
		Sleep(200);
		if (shapeP1 == false)
		{
			//board.printFreeSpace(0, 0);
			s.setShape(254);
			isDeleted = board.checkFullLine();
			//board.print();
			if (isDeleted)
			{
				board.printFreeSpace();
				isDeleted = false;
			}
		}
	}
	
	//int menuInput = game.printMenu(false);
	//switch (menuInput)
	//{
	//case 1:
	//	game.runGame();
	//case 8:
	//	game.printInstructions(); //Will code this function later
	//	break;
	//}
}