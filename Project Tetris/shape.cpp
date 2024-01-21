#include "shape.h"

Shape::Shape(Board& _board, char ch) : board(_board)
{
	setShape(ch);
}

//Shape& Shape::operator=(const Shape& newShape)
//{
//	this->board = newShape.board;
//
//	return *this;
//}

void Shape::setShape(char ch)
{
	int positions[8] = {};
	randomShape(positions);
	orientation = 0; //change to enum later
	for (int i = 0; i < 8; i += 2)
	{
		blockArr[i/2].setChar(ch);
		blockArr[i/2].setCords(positions[i], positions[i + 1]);

	}
}

void Shape::randomShape(int positions[8]) 
{
	//srand(time(nullptr));
	int anchorX = board.X_START + board.WIDTH / 2, anchorY = board.Y_START + 1;
	shape = (Shapes)(rand() % 7);
	//shape = (Shapes)(0);
	switch (shape) 
	{
	case Shapes::I: 
		divider = 2;
		createCordsArr(positions, anchorX, anchorY, -1, 0, 1, 0, 2, 0);
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
		createCordsArr(positions, anchorX, anchorY, 1, 0, -1, 0, 1, 1);
		break;
	case Shapes::L: 
		divider = 4;
		createCordsArr(positions, anchorX, anchorY, -1, 0, 1, 0, -1, 1);
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
	//handleInput(board.playerNum);
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
			board.freeSpace[blockArr[i].y - board.Y_START][blockArr[i].x - board.X_START] = blockArr[i].ch;
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

//void Shape::handleInput(int playerNum)
//{
//	if (_kbhit())
//	{
//		char key = _getch();
//		switch (key)
//		{
//		case (char)GameConfig::Lkeys::LEFT:
//		case (char)GameConfig::Lkeys::RIGHT:
//			moveShapeLeftRight(key, playerNum);
//			break;
//		case (char)GameConfig::Lkeys::ESC:
//			Game::printMenu(true);
//			break;
//		case (char)GameConfig::Lkeys::DOWN:
//			moveShapeToBottom();
//			break;
//		case (char)GameConfig::Lkeys::CLOCKWISE:
//		case (char)GameConfig::Lkeys::COUNTER_CLOCKWISE:
//			rotateShape(key);
//			break;
//		}
//	}
//}

void Shape::speedUpShape()
{
	bool cantMove = false;
	//int freeSpaceX, freeSpaceY;
	for (int i = 0; i < 4; i++)
	{
		if (blockArr[i].checkFreeSpaceOffset(0, 2, board) == true)
		{
			cantMove = true;
			break;
		}
	}

	if (!cantMove)
	{
		moveBy(0, 2);
		print();
	}
} //Might delete function

void Shape::rotateShape(char key)
{ 
	int positions[8] = {};
	int anchorX = blockArr[0].x, anchorY = blockArr[0].y;
	int nextOrientation = getNextOrientation(key);

	switch (shape)
	{
	case Shapes::I:
		if (orientation == 0) 
			createCordsArr(positions, anchorX, anchorY, 0, -1, 0, 1, 0, 2); //orientation 1
		else
			createCordsArr(positions, anchorX, anchorY, -1, 0, 1, 0, 2, 0); //orientation 0
		break;
	case Shapes::T:
		if (nextOrientation == 1)
		    createCordsArr(positions, anchorX, anchorY, 0, -1, 0, 1, 1, 0); //orientation 1
		else if (nextOrientation == 2)
			createCordsArr(positions, anchorX, anchorY, 1, 0, -1, 0, 0, -1); //orientation 2
		else if (nextOrientation == 3)
			createCordsArr(positions, anchorX, anchorY, 0, -1, 0, 1, -1, 0); //orientation 3
		else
			createCordsArr(positions, anchorX, anchorY, 1, 0, 0, 1, -1, 0); //orientation 0
		break;
	case Shapes::S:
		if (orientation == 0)
		    createCordsArr(positions, anchorX, anchorY, -1, 0, -1, -1, 0, 1); //orientation 1
		else
			createCordsArr(positions, anchorX, anchorY, 1, 0, 0, 1, -1, 1); //orientation 0
		break;
	case Shapes::Z:
		if (orientation == 0)
		    createCordsArr(positions, anchorX, anchorY, -1, 0, -1, 1, 0, -1);//orientation 1
		else
			createCordsArr(positions, anchorX, anchorY, -1, 0, 0, 1, 1, 1); //orientation 0
		break;
	case Shapes::J:
		if (nextOrientation == 1)
			createCordsArr(positions, anchorX, anchorY, 0, -1, 0, 1, 1, -1); //orientation 1
		else if (nextOrientation == 2)
			createCordsArr(positions, anchorX, anchorY, 1, 0, -1, 0, -1, -1); //orientation 2
		else if (nextOrientation == 3)
			createCordsArr(positions, anchorX, anchorY, 0, -1, 0, 1, -1, 1); //orientation 3
		else
			createCordsArr(positions, anchorX, anchorY, 1, 0, -1, 0, 1, 1); //orientation 0
		break;
	case Shapes::L:
		if (nextOrientation == 1)
			createCordsArr(positions, anchorX, anchorY, 0, -1, 0, 1, 1, 1); //orientation 1
		else if (nextOrientation == 2)
			createCordsArr(positions, anchorX, anchorY, -1, 0, 1, 0, 1, -1); //orientation 2
		else if (nextOrientation == 3)
			createCordsArr(positions, anchorX, anchorY, 0, 1, 0, -1, -1, -1); //orientation 3
		else
			createCordsArr(positions, anchorX, anchorY, -1, 0, 1, 0, -1, 1); //orientation 0
		break;
	}

	orientation = nextOrientation;
	changeShapePosition(positions);
}

void Shape::changeShapePosition(int positions[8])
{
	bool cantMove = false;
	for (int i = 1; i < 4; i++)
	{
		if (board.checkFreeSpaceCoordinates(positions[i * 2] - board.X_START, positions[i * 2 + 1] - board.Y_START) == true)
			cantMove = true;
		//if (blockArr[i].checkFreeSpaceOffset(positions[i * 2], positions[i * 2 + 1], board) == true)
		//	cantMove = true;
	}
	if (!cantMove)
	{
		for (int i = 1; i < 4; i++)
		{
			blockArr[i].moveTo(positions[i * 2], positions[i * 2 + 1]);
		}
		print();
	}
}

int Shape::getNextOrientation(int key)
{
	int nextOrientation;

	if (key == (char)GameConfig::Lkeys::CLOCKWISE)
		nextOrientation = (orientation + 1) % divider;
	else
		nextOrientation = orientation - 1;

	if (nextOrientation == -1)
		nextOrientation = divider - 1;

	return nextOrientation;
}



