#include "shape.h"

Shape::Shape(string string, const Board& _board, char ch) : board(_board)
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

void Shape::moveShapeDown()
{
	/*for (int i = 0; i < board.HEIGHT - 1; i++)
	{*/
		moveShapeLeftRight(board.playerNum);
		moveBy(0, 1);
		print();
	//}

}

void Shape::moveShapeLeftRight(int playerNum)
{
	if (_kbhit())
	{
		char key = _getch();
		for (int i = 0; i < 4; i++)
		{
			blockArr[i].moveBlockLeftRight(key, playerNum);
		}
	}
}


