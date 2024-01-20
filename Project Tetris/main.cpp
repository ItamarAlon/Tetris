#include "Libraries.h"
#include "block.h"
#include "Board.h"
#include "shape.h"


void main()
{
	Board board;
	//board.printFreeSpace(0,0);
	bool shapeP1 = true;
	Shape s(board);
	bool isDeleted=false;


	//board.print();
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
	
	////DON'T DELETE::
	//int menuInput = Game::printMenu(false);
	//switch (menuInput)
	//{
	//case 1:
	//	board.print();
	//	while (true)
	//	{
	//		shapeP1 = s.moveShapeDown();
	//		Sleep(300);
	//		if (shapeP1 == false)
	//			s.setShape(254);
	//	}
	//	break;
	//case 8:
	//	Game::printInstructions(); //Will code this function later
	//	break;
	//}
}