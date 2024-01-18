#include "shape.h"

Shape::Shape(const Board& _board, char ch) : board(_board)
{
	setShape(ch);
}

void Shape::setShape(char ch)
{
	int positions[8] = {};
	randomShape(positions);
	orientation = 0; //change to enum later
	for (int i = 0; i < 8; i += 2)
	{

		blockArr[i/2].setChar(254);
		blockArr[i/2].setCords(positions[i], positions[i + 1]);

	}
}

void Shape::randomShape(int positions[8]) {
	srand(time(nullptr));
	int anchorX = board.X_START + board.WIDTH / 2, anchorY = board.Y_START + 1;
	//shape = (Shapes)(rand() % 7);
	shape = (Shapes)(0);
	switch (shape) {
	case Shapes::I:
		divider = 2;
		createCordsArr(positions, anchorX, anchorY, 1, 0, 2, 0, 3, 0);
		break;
	case Shapes::O:
		divider = 1;
		createCordsArr(positions, anchorX, anchorY, 1, 0, 0, 1, 1, 1);
		break;
	case Shapes::T:
		divider = 4;
		createCordsArr(positions, anchorX, anchorY, 1, 0, 0, 1, -1, 0);
		break;
	case Shapes::S:
		divider = 2;
		createCordsArr(positions, anchorX, anchorY, 1, 0, 0, 1, -1, 1);
		break;
	case Shapes::Z:
		divider = 2;
		createCordsArr(positions, anchorX, anchorY, -1, 0, 0, 1, 1, 1);
		break;
	case Shapes::J:
		divider = 4;
		createCordsArr(positions, anchorX, anchorY, 1, 0, 2,0, 0, 1);
		break;
	case Shapes::L:
		divider = 4;
		createCordsArr(positions, anchorX, anchorY, -1,0, -2, 0, 0, 1);
		break;
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
		blockArr[i].moveBy(x, y);
	}

}

bool Shape::moveShapeDown()
{
	bool cantMove = false;
	handleInput(board.playerNum);
	for (int i = 0; i < 4; i++)
	{
		if (blockArr[i].checkFreeSpaceOffset(0, 1, board) == true)
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

void Shape::moveShapeLeftRight(int key, int playerNum)
{
	int offsetX, offsetY;
	bool cantMove = false;

	for (int i = 0; i < 4; i++)
	{
		blockArr[i].getOffsetFromInput(key, offsetX, offsetY);
		if (blockArr[i].checkFreeSpaceOffset(offsetX, offsetY, board) == true)
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

void Shape::createCordsArr(int positions[8], int anchorX, int anchorY, int x1, int y1, int x2, int y2, int x3, int y3)
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

void Shape::handleInput(int playerNum)
{
	if (_kbhit())
	{
		char key = _getch();
		switch (key)
		{
		case (char)GameConfig::Lkeys::LEFT:
		case (char)GameConfig::Lkeys::RIGHT:
			moveShapeLeftRight(key, playerNum);
			break;
		case (char)GameConfig::Lkeys::ESC:
			Game::printMenu(true);
			break;
		case (char)GameConfig::Lkeys::DOWN:
			moveShapeToBottom();
			break;
		case (char)GameConfig::Lkeys::CLOCKWISE:
		case (char)GameConfig::Lkeys::COUNTER_CLOCKWISE:
			rotateShape(key);
			break;
		}
	}
}

void Shape::moveShapeToBottom()
{
	int j, minDistance = board.HEIGHT + 10;
	//int freeSpaceX, freeSpaceY;
	for (int i = 0; i < 4; i++)
	{
		//blockArr[i].getFreeSpaceXY(board, freeSpaceX, freeSpaceY);
		j = board.HEIGHT;
		while (blockArr[i].checkFreeSpaceOffset(0, j, board) == false)
			j--;
		if (j < minDistance)
			minDistance = j;
	}
	moveBy(0, minDistance);
	print();
}

void Shape::rotateShape(char key)
{
	bool cantMove = false;
	int positions[8] = {};
	int anchorX = blockArr[0].x, anchorY = blockArr[0].y;
	switch (shape)
	{
	case Shapes::I:
		if (orientation == 0)
			createCordsArr(positions, anchorX, anchorY, 0, -1, 0, 1, 0, 2);
		else
			createCordsArr(positions, anchorX, anchorY, -1, 0, 1, 0, 2, 0);
		orientation = (orientation + 1) % divider;
	}
	for (int i = 1; i < 4; i++)
	{
		if (blockArr[i].checkFreeSpaceOffset(positions[i*2], positions[i * 2+1], board) == true)
			cantMove = true;
	}
	if(!cantMove)
	{
		for (int i = 1; i < 4; i++)
		{
			blockArr[i].moveTo(positions[i * 2], positions[i * 2 + 1]);
		}
		print();

	}
}



