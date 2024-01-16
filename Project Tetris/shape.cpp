#include "shape.h"

Shape::Shape(string string, const Board& _board, char ch) : board(_board)
{
	//int k = 0;
	//for (int i = 0; i < 4; i++)
	//{
	//	if (string[k] != ' ')
	//	{
	//		blockArr[i].setChar(ch);
	//		blockArr[i].setCords(i + board.X_START + board.WIDTH / 2, board.Y_START + 1);
	//		//block.setCords(X_START + WIDTH / 2, Y_START + 1);
	//	}
	//	k++;
	//	
	//}

	setShape(string, ch);

}

void Shape::setShape(string string, char ch)
{
	int k = 0;
	for (int i = 0; i < 4; i++)
	{
		if (string[k] != ' ')
		{
			blockArr[i].setChar(ch);
			blockArr[i].setCords(i + board.X_START + board.WIDTH / 2, board.Y_START + 1);
			//block.setCords(X_START + WIDTH / 2, Y_START + 1);
		}
		k++;

	}
}

void Shape::print()
{
	for (int i = 0; i < 4; i++)
	{
		if (blockArr[i].ch != ' ')
			blockArr[i].print();

	}
}

void Shape::moveBy(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		/*	gotoxy(blockArr[i].x, blockArr[i].y);
			cout << " ";*/
		blockArr[i].moveBy(x, y);
	}

}

bool Shape::moveShapeDown()
{
	bool cantMove = false;
	moveShapeLeftRight(board.playerNum);
	for (int i = 0; i < 4; i++)
	{
		if (blockArr[i].checkFreeSpace(0, 1, board) == true)
			cantMove = true;
	}
	if (cantMove == false)
	{
		moveBy(0, 1);
		print();
		return true;
	}
	else
	{
		for (int i = 0; i < 4; i++)
			board.freeSpace[blockArr[i].x - board.X_START][blockArr[i].y - board.Y_START] = false;
		return false;
	}
}

void Shape::moveShapeLeftRight(int playerNum)
{
	int offsetX, offsetY;
	bool cantMove = false;
	if (_kbhit())
	{
		char key = _getch();
		for (int i = 0; i < 4; i++) {
			blockArr[i].getOffsetFromInput(key, offsetX, offsetY);
			if (blockArr[i].checkFreeSpace(offsetX, offsetY, board) == true)
				cantMove = true;
		}
		if (cantMove == false)
		{
			for (int i = 0; i < 4; i++)
			{
				blockArr[i].moveBlockLeftRight(key, playerNum);
			}
		}
	}
}


