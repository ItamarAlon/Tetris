#include "shape.h"

Shape::Shape(string string, const Board& _board, char ch) : board(_board)
{
	setShape(string, ch);
}

void Shape::setShape(string string, char ch)
{
	int  positions[8] = {};
	randomShape(positions);
	for (int i = 0; i < 8; i += 2)
	{

		blockArr[i/2].setChar(254);
		blockArr[i/2].setCords(positions[i], positions[i + 1]);


	}
}

void Shape::randomShape(int positions[8]) {
	srand(time(nullptr));
	int anchorX = board.X_START + board.WIDTH / 2, anchorY = board.Y_START + 1;
	int shape = rand() % 7;
	switch (shape) {
	case (int)Shapes::I:
		createShape(positions, anchorX, anchorY, 1, 0, 2, 0, 3, 0);
		break;
	case (int)Shapes::O:
		createShape(positions, anchorX, anchorY, 1, 0, 0, 1, 1, 1);
		break;
	case(int)Shapes::T:
		createShape(positions, anchorX, anchorY, 1, 0, 0, 1, -1, 0);
		break;
	case(int)Shapes::S:
		createShape(positions, anchorX, anchorY, 1, 0, 0, 1, -1, 1);
		break;
	case(int)Shapes::Z:
		createShape(positions, anchorX, anchorY, -1, 0, 0, 1, 1, 1);
		break;
	case(int)Shapes::J:
		createShape(positions, anchorX, anchorY, 1, 0, 2,0, 0, 1);
		break;
	case(int)Shapes::L:
		createShape(positions, anchorX, anchorY, -1,0, -2, 0, 0, 1);
		break;
	}
}
//{I,O,T,S,Z,J,L};
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

void Shape::createShape(int positions[8], int anchorX, int anchorY, int x1, int y1, int x2, int y2, int x3, int y3)
{
	positions[0] = anchorX;
	positions[1] = anchorY;
	positions[2] = anchorX + x1;
	positions[3] = anchorY + y1;
	positions[4] = anchorX + x2;
	positions[5] = anchorY + y2;
	positions[6] = anchorX + x3;
	positions[7] = anchorY + y3;
}


