#include "shape.h"

Shape::Shape(Board& _board, char _ch) : board(_board), ch(_ch)
{
	setShape();
}

Shape::Shape(const Shape& oldShape) : board(oldShape.board), ch(oldShape.ch)
{
	shape = oldShape.shape;
	orientation = oldShape.orientation;
	divider = oldShape.divider;

	for (int i = 0; i < 4; i++)
	{
		blockArr[i].setChar(oldShape.ch);
		blockArr[i].setCords(oldShape.blockArr[i].getX(), oldShape.blockArr[i].getY()); //Set the cords of every block in the array, from the positions array
	}
}

void Shape::setShape()
{
	int positions[8] = {};
	randomShape(positions); //Function generates a random shape (out of the 7 shapes in the game) by giving coordinates of 4 blocks (which make a tetromino) to a positions array.
	orientation = 0; //The beginning orientation of the shape will always be 0;
	for (int i = 0; i < 8; i += 2)
	{
		blockArr[i/2].setChar(ch);
		blockArr[i/2].setCords(positions[i], positions[i + 1]); //Set the cords of every block in the array, from the positions array
	}
}

void Shape::randomShape(int positions[8]) 
{
	////coordinates (on-screen) of the "anchor" block, which is the main block of the shape (all the other block's coordinates are determined by the coordinates of the anchor block)
	//int anchorX = board.getXStart() + board.getWidth() / 2; //the anchor block will always by in the middle of the board (on the X axis)
	//int	anchorY = board.getYStart() + 1;
	//
	//shape = (Shapes)(rand() % 7); //generate a random number from 0-6, each represents a different tetromino shape
	//switch (shape) //the empty positions array given to the function is set by the shape that was generated
	//{
	//case Shapes::I: 
	//	divider = 2;//Another function is used to fill the positions array. The anchor cords will be set in the beginning, and the rest of the integers are offset cords (relative to the anchor itself)
	//	createCordsArr(positions, anchorX, anchorY, -1, 0, 1, 0, 2, 0); //For example here, The function receives the anchor cords, and the 3 non-anchor blocks are placed on the left of anchor, the right of anchor, and 2 places to the right of anchor. That creates an I shape.
	//	break;
	//case Shapes::O: 
	//	divider = 1;
	//	createCordsArr(positions, anchorX, anchorY, 1, 0, 0, 1, 1, 1);
	//	break;
	//case Shapes::T: 
	//	divider = 4;
	//	createCordsArr(positions, anchorX, anchorY, 1, 0, 0, 1, -1, 0); 
	//	break;
	//case Shapes::S: 
	//	divider = 2;
	//	createCordsArr(positions, anchorX, anchorY, 1, 0, 0, 1, -1, 1);
	//	break;
	//case Shapes::Z: 
	//	divider = 2;
	//	createCordsArr(positions, anchorX, anchorY, -1, 0, 0, 1, 1, 1);
	//	break;
	//case Shapes::J: 
	//	divider = 4;
	//	createCordsArr(positions, anchorX, anchorY, 1, 0, -1, 0, 1, 1);
	//	break;
	//case Shapes::L: 
	//	divider = 4;
	//	createCordsArr(positions, anchorX, anchorY, -1, 0, 1, 0, -1, 1);
	//	break;
	//}

	shape = (Shapes)(rand() % 7); //generate a random number from 0-6, each represents a different tetromino shape
	getSpawnCords(positions);
}

void Shape::print()
{
	for (int i = 0; i < 4; i++)
	{
		if (blockArr[i].getChar() != ' ')
			blockArr[i].print();
	}
}

void Shape::moveBy(int x, int y)
{
	for (int i = 0; i < 4; i++)
		blockArr[i].moveBy(x, y); //moves every block in the shape by x and y values
	print(); //temp
}

bool Shape::moveShapeDown()
{
	//bool cantMove = false;
	//for (int i = 0; i < 4; i++)
	//{
	//	if (blockArr[i].isSpaceTakenOffset(0, 1, board)) //checks for every block, if the space under it is free or not
	//	{
	//		cantMove = true; //If the space is taken, then the shape can't move
	//		break;
	//	}
	//}
	//if (!cantMove) //If the shape can move down...
	//{
	//	moveBy(0, 1); //... then it moves down by 1 block
	//	print();
	//	return true; //The function returns true because the shape was still in the air (because the space under it is free)
	//}
	//else //If the shape can't move, then it's on the ground. So we update freeSpace so the program will remember that there are blocks there
	//{
	//	int freeSpaceX, freeSpaceY;
	//
	//	for (int i = 0; i < 4; i++) 
	//	{
	//		blockArr[i].getFreeSpaceXY(board, freeSpaceX, freeSpaceY); //We get the cords (in freeSpace) of the block in the array
	//		board.setFreeSpaceValue(ch, freeSpaceX, freeSpaceY); //...and update freeSpace accordingly
	//	}
	//	return false; //because the shape can't move, then it's on the ground. So the function returns false (is used in the game class later)
	//}

	if (canShapeMove(0, 1)) //If the shape can move down...
	{
		moveBy(0, 1); //... then it moves down by 1 block
		print();
		return true; //The function returns true because the shape was still in the air (because the space under it is free)
	}
	else //If the shape can't move, then it's on the ground. So we update freeSpace so the program will remember that there are blocks there
	{
		glueShape();
		return false; //because the shape can't move, then it's on the ground. So the function returns false (is used in the game class later)
	}
}

bool Shape::moveShapeLeftRight(int input)
{
	//int offsetX, offsetY;
	//bool cantMove = false;
	//blockArr[0].getOffsetFromInput(input, offsetX, offsetY); //Function returns the offset of x and y for all block in the Tetromino, which depends on the input given by the player
	//
	//for (int i = 0; i < 4; i++)
	//{
	//	if (blockArr[i].isSpaceTakenOffset(offsetX, offsetY, board))
	//		cantMove = true; //If the place that one of the blocks are set to move to is taken, than the Tetromino can't move
	//}
	//if (!cantMove)
	//{
	//	for (int i = 0; i < 4; i++)
	//		blockArr[i].moveBlockLeftRight(input); //If the shape can move, we move all the blocks (depending on the input) 
	//	print();
	//}

	int offsetX, offsetY;
	blockArr[0].getOffsetFromInput(input, offsetX, offsetY); //Function returns the offset of x and y for all block in the Tetromino, which depends on the input given by the player

	if (!canShapeMove(offsetX, offsetY))
		return false;

	for (int i = 0; i < 4; i++)
		blockArr[i].moveBlockLeftRight(input); //If the shape can move, we move all the blocks (depending on the input) 
	print();
	return true;
}

void Shape::createCordsArr(int positions[8], int anchorX, int anchorY, int x1, int y1, int x2, int y2, int x3, int y3)
{
	positions[0] = anchorX; //At first, anchorX and Y are set
	positions[1] = anchorY;
	positions[2] = anchorX + x1;//Then, the offsets are set (in relative to the anchor)
	positions[3] = anchorY + y1;
	positions[4] = anchorX + x2;
	positions[5] = anchorY + y2;
	positions[6] = anchorX + x3;
	positions[7] = anchorY + y3;
}

void Shape::rotateShape(char input)
{ 
	int positions[8] = {};
	int anchorX = blockArr[0].getX(), anchorY = blockArr[0].getY(); 
	int nextOrientation = getNextOrientation(input);

	//The function saves in positions[] the cords of the next orientation of the Tetromino (according to it's shape)
	//It's worth pointing out that the O shape doesn't appear here, because it can't rotate. If the player tries to rotate it, nothing happens
	switch (shape)
	{
	case Shapes::I:
		if (nextOrientation == 1)
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
		if (nextOrientation == 1)
		    createCordsArr(positions, anchorX, anchorY, -1, 0, -1, -1, 0, 1); //orientation 1
		else
			createCordsArr(positions, anchorX, anchorY, 1, 0, 0, 1, -1, 1); //orientation 0
		break;
	case Shapes::Z:
		if (nextOrientation == 1)
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

	if (changeShapePosition(positions)) //A function is used to change the position of all the block according to the positions array. If it succeeds in doing so, it returns true
	{
		print();
		orientation = nextOrientation; //If the Tetromino was rotated, orientation is updated
	}
}

bool Shape::changeShapePosition(int positions[8])
{
	bool cantMove = false;
	for (int i = 1; i < 4; i++)
	{
		if (board.isSpaceTaken(positions[i * 2] - board.getXStart(), positions[i * 2 + 1] - board.getYStart())) //If the position that the block wants to move to is take...
			cantMove = true; //... cantMove is updated accordingly
	}
	if (!cantMove)
	{
		for (int i = 0; i < 4; i++)
			blockArr[i].moveTo(positions[i * 2], positions[i * 2 + 1]); //If the shape can move, than we move all blocks to their positions (from the positions array)
		return true; //Because the shape changed it's position, true is returned
	}
	return false;
}

int Shape::getNextOrientation(int key)
{
	int nextOrientation;

	if (key == (char)GameConfig::Lkeys::CLOCKWISE)
		nextOrientation = (orientation + 1) % divider; //If rotating clockwise was chosen, we go to the nextOrientation (which returns to 0 after going through all orientations, which is why module is used
	else
		nextOrientation = orientation - 1; //Otherwise, orientation goes down by 1, which can cause it to turn -1 (which is illegal).

	if (nextOrientation == -1) //so if the orientation is -1, we change it to the last orientation
		nextOrientation = divider - 1;

	return nextOrientation;
}

bool Shape::canShapeMove(int offsetX, int offsetY)
{
	for (int i = 0; i < 4; i++)
		if (blockArr[i].isSpaceTakenOffset(offsetX, offsetY, board)) //checks for every block, if the space under it is free or not
			return false; //If the space is taken, then the shape can't move
	return true;
}

int Shape::getAnchorX() const
{
	return blockArr[0].getX();
}

int Shape::getAnchorY() const
{
	return blockArr[0].getY();
}

void Shape::getAnchorXY(int& anchorX, int& anchorY) const
{
	anchorX = getAnchorX();
	anchorY = getAnchorY();
}

void Shape::glueShape()
{
	int freeSpaceX, freeSpaceY;

	for (int i = 0; i < 4; i++)
	{
		blockArr[i].getFreeSpaceXY(board, freeSpaceX, freeSpaceY); //We get the cords (in freeSpace) of the block in the array
		board.setFreeSpaceValue(ch, freeSpaceX, freeSpaceY); //...and update freeSpace accordingly
	}
}

void Shape::unGlueShape()
{
	int freeSpaceX, freeSpaceY;

	for (int i = 0; i < 4; i++)
	{
		blockArr[i].getFreeSpaceXY(board, freeSpaceX, freeSpaceY); //We get the cords (in freeSpace) of the block in the array
		board.setFreeSpaceValue(' ', freeSpaceX, freeSpaceY); //...and update freeSpace accordingly
	}
}

void Shape::teleportToFloor()
{
	while (canShapeMove(0, 1))
		moveBy(0, 1);
}

int Shape::getOrientation() const
{
	return orientation;
}

int Shape::getDivider() const
{
	return divider;
}

void Shape::getSpawnCords(int positions[8])
{
	int anchorX = board.getXStart() + board.getWidth() / 2; //the anchor block will always by in the middle of the board (on the X axis)
	int	anchorY = board.getYStart() + 1;

	switch (shape) //the empty positions array given to the function is set by the shape that was generated
	{
	case Shapes::I:
		divider = 2;//Another function is used to fill the positions array. The anchor cords will be set in the beginning, and the rest of the integers are offset cords (relative to the anchor itself)
		createCordsArr(positions, anchorX, anchorY, -1, 0, 1, 0, 2, 0); //For example here, The function receives the anchor cords, and the 3 non-anchor blocks are placed on the left of anchor, the right of anchor, and 2 places to the right of anchor. That creates an I shape.
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



