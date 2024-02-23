#include "shape.h"

Shape::Shape(Board& _board, char _ch) : board(_board), ch(_ch)
{
	setShape(false);
}

Shape::Shape(const Shape& oldShape) : board(oldShape.board)
{
	*this = oldShape;
}

Shape& Shape::operator=(const Shape& oldShape)
{
	if (&oldShape != this)
	{
		board = oldShape.board;
		ch = oldShape.ch;
		shape = oldShape.shape;
		orientation = oldShape.orientation;
		divider = oldShape.divider;

		for (int i = 0; i < 4; i++)
		{
			blockArr[i].setChar(oldShape.ch);
			blockArr[i].setCords(oldShape.blockArr[i].getX(), oldShape.blockArr[i].getY()); //Set the cords of every block in the array, from the positions array
		}
	}
	return *this;
}

void Shape::setShape(bool allowBomb)
{
	int positions[8] = {};
	randomShape(positions); //Function generates a random shape (out of the 7 regular shapes in the game) by giving coordinates of 4 blocks (which make a tetromino) to a positions array.
	for (int i = 0; i < 8; i += 2)
	{
		blockArr[i / 2].setChar(ch);
		blockArr[i / 2].setCords(positions[i], positions[i + 1]); //Set the cords of every block in the array, from the positions array
	}
}

void Shape::setBomb()
{
	divider = 1;
	numOfBlocks = 1; //A bomb has 1 block
	shape = Shapes::BOMB;

	int anchorX = board.getXStart() + board.getWidth() / 2;
	int	anchorY = board.getYStart() + 1;
	blockArr[0].setCords(anchorX, anchorY);

	for (int i = 1; i < 4; i++)
		blockArr[i].setChar(' '); //The rest of the block are irrelevant
}

void Shape::randomShape(int positions[8]) 
{
	shape = (Shapes)(rand() % 7); //generate a random number from 0-6, each represents a different tetromino shape
	getSpawnCords(positions);
}

void Shape::print()
{
	for (int i = 0; i < numOfBlocks; i++)
	{
		if (blockArr[i].getChar() != ' ')
			blockArr[i].print();
	}
}

void Shape::moveBy(int x, int y) 
{
	for (int i = 0; i < numOfBlocks; i++)
		blockArr[i].moveBy(x, y); //moves every block in the shape by x and y values
}

bool Shape::moveShapeDown() 
{
	if (canShapeMoveOffset(0, 1)) //If the shape can move down...
	{
		moveBy(0, 1); //... then it moves down by 1 block
		print();
		return true; //The function returns true because the shape was still in the air (because the space under it is free)
	}
	else //If the shape can't move, then it's on the ground. So we update freeSpace so the program will remember that there are blocks there
	{
		glueShape(); //The shape is "glued" to the board
		print();
		return false; //because the shape can't move, then it's on the ground. So the function returns false (is used in the game class later)
	}
}

bool Shape::moveShapeLeftRight(int offsetX)
{
	if (!canShapeMoveOffset(offsetX, 0))
		return false;

	moveBy(offsetX, 0); //If the shape can move, we move it (depending on offsetX)
	print();
	return true;
}

void Shape::rotateShape(int newOrientation)
{ 
	if (newOrientation >= divider || newOrientation < 0)
		newOrientation = 0;

	int positions[8] = {};
	int anchorX = blockArr[0].getX(), anchorY = blockArr[0].getY(); 

	//The function saves in positions[] the cords of the next orientation of the Tetromino (according to it's shape)
	//It's worth pointing out that the O shape doesn't appear here, because it can't rotate. If the player tries to rotate it, nothing happens
	switch (shape)
	{
	case Shapes::I:
		if (newOrientation == 1)
			createCordsArr(positions, anchorX, anchorY, 0, -1, 0, 1, 0, 2); //orientation 1
		else
			createCordsArr(positions, anchorX, anchorY, -1, 0, 1, 0, 2, 0); //orientation 0
		break;
	case Shapes::T:
		if (newOrientation == 1)
		    createCordsArr(positions, anchorX, anchorY, 0, -1, 0, 1, 1, 0); //orientation 1
		else if (newOrientation == 2)
			createCordsArr(positions, anchorX, anchorY, 1, 0, -1, 0, 0, -1); //orientation 2
		else if (newOrientation == 3)
			createCordsArr(positions, anchorX, anchorY, 0, -1, 0, 1, -1, 0); //orientation 3
		else
			createCordsArr(positions, anchorX, anchorY, 1, 0, 0, 1, -1, 0); //orientation 0
		break;
	case Shapes::S:
		if (newOrientation == 1)
		    createCordsArr(positions, anchorX, anchorY, -1, 0, -1, -1, 0, 1); //orientation 1
		else
			createCordsArr(positions, anchorX, anchorY, 1, 0, 0, 1, -1, 1); //orientation 0
		break;
	case Shapes::Z:
		if (newOrientation == 1)
		    createCordsArr(positions, anchorX, anchorY, -1, 0, -1, 1, 0, -1);//orientation 1
		else
			createCordsArr(positions, anchorX, anchorY, -1, 0, 0, 1, 1, 1); //orientation 0
		break;
	case Shapes::J:
		if (newOrientation == 1)
			createCordsArr(positions, anchorX, anchorY, 0, -1, 0, 1, 1, -1); //orientation 1
		else if (newOrientation == 2)
			createCordsArr(positions, anchorX, anchorY, 1, 0, -1, 0, -1, -1); //orientation 2
		else if (newOrientation == 3)
			createCordsArr(positions, anchorX, anchorY, 0, -1, 0, 1, -1, 1); //orientation 3
		else
			createCordsArr(positions, anchorX, anchorY, 1, 0, -1, 0, 1, 1); //orientation 0
		break;
	case Shapes::L:
		if (newOrientation == 1)
			createCordsArr(positions, anchorX, anchorY, 0, -1, 0, 1, 1, 1); //orientation 1
		else if (newOrientation == 2)
			createCordsArr(positions, anchorX, anchorY, -1, 0, 1, 0, 1, -1); //orientation 2
		else if (newOrientation == 3)
			createCordsArr(positions, anchorX, anchorY, 0, 1, 0, -1, -1, -1); //orientation 3
		else
			createCordsArr(positions, anchorX, anchorY, -1, 0, 1, 0, -1, 1); //orientation 0
		break;
	}

	if (changeShapePosition(positions)) //A function is used to change the position of all the block according to the positions array. If it succeeds in doing so, it returns true
		orientation = newOrientation; //If the Tetromino was rotated, orientation is updated
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

void Shape::updateBestPosition(float score, Position& bestPosition)
{
	if (score > bestPosition.score)
	{
		getAnchorXY(bestPosition.anchorX, bestPosition.anchorY); //the current best position is updated if the score of the current position is higher
		bestPosition.score = score;
		bestPosition.orientation = getOrientation();
	}
}

void Shape::updateWorstPosition(float score, Position& worstPosition)
{
	if (score < worstPosition.score) //Similar for worst position
	{
		getAnchorXY(worstPosition.anchorX, worstPosition.anchorY);
		worstPosition.score = score;
		worstPosition.orientation = getOrientation();
	}
}

bool Shape::changeShapePosition(int positions[8])
{
	if (canShapeMoveToPosition(positions))
	{
		for (int i = 0; i < numOfBlocks; i++)
			blockArr[i].moveTo(positions[i * 2], positions[i * 2 + 1]); //If the shape can move, than we move all blocks to their positions (from the positions array)
		return true; //Because the shape changed it's position, true is returned
	}
	return false;
}

bool Shape::canShapeMoveOffset(int offsetX, int offsetY)
{
	for (int i = 0; i < numOfBlocks; i++)
		if (blockArr[i].isSpaceTakenOffset(offsetX, offsetY, board)) //checks for every block, if the space under it is free or not
			return false; //If the space is taken, then the shape can't move
	return true;
}

bool Shape::canShapeMoveToPosition(int positions[8]) const
{
	int freeSpaceX, freeSpaceY;

	for (int i = 0; i < numOfBlocks; i++)
	{
		board.convertXYToFreeSpaceXY(positions[i * 2], positions[i * 2 + 1], freeSpaceX, freeSpaceY);

		if (board.isSpaceTaken(freeSpaceX, freeSpaceY)) //If the position that the block wants to move to is taken...
			return false; //...false is returned
	}
	return true; //Else (if the Shape can move to the position), true is returned
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

bool Shape::isBomb() const
{
	return false;
}

int Shape::getDistanceFromBorder(GameConfig::Direction direction)
{
	int offset = getOffsetX(direction);
	int distance = 0;

	while (canShapeMoveOffset(offset, 0)) 
	{
		moveBy(offset, 0); //The shape moves all the way the the given direction until it can't
		distance++;
	}

	moveBy(-offset * distance, 0); //Then, we move it back to where it was (using the distance we got)
	return distance;
}

void Shape::moveAllTheWay(GameConfig::Direction direction)
{
	int distance = getDistanceFromBorder(direction); //gets the distance from the boarder
	moveBy(distance * getOffsetX(direction), 0); //Moves that distance
}

int Shape::getOffsetX(GameConfig::Direction direction)
{
	switch (direction)
	{
	case GameConfig::Direction::LEFT:
		return -1;
	case GameConfig::Direction::RIGHT:
		return 1;
	default:
		return 0;
	}
}

void Shape::findBestAndWorstPosition(Position& best, Position& worst)
{
	ShowConsoleCursor(false);
	best.score = -9999999; //At the beginning, the best position gets a low score so it will be updated during search
	worst.score = 9999999;
	float score;
	int divider = getDivider();
	int spawnCords[8] = {};
	getSpawnCords(spawnCords); //Spawn cords of the shape

	for (int i = 0; i < divider; i++)
	{
		moveAllTheWay(GameConfig::Direction::LEFT);

		while (true)
		{
			teleportToFloor();

			score = getPositionScore(); //For every run of the loop, we move the shape to the floor, calculates it's position's score...
			updateBestPosition(score, best); //Update the score accordingly..
			updateWorstPosition(score, worst);

			teleportToCeiling(); //Teleport it to the ceiling...

			if (canShapeMoveOffset(1, 0))
				moveBy(1, 0); //And moving it to the left if possible
			else
			{
				changeShapePosition(spawnCords); //If it already reached the end of the search, we return it back to spawn
				break;
			}
		}
		moveBy(0, 1);
		rotateShape(orientation + 1); //Afterwards the shape is rotated before checking the best move for a new rotation
	}
}

float Shape::getPositionScore()
{
	const Board temp = board; //We copy the board before calculating, to not ruin it during search
	glueShape(); //We glue the shape (so we can check the score)

	int holeCount, fullLinesCount; //The score is calculated by those 3 values
	float bumpiness;
	int holeWeight, bumpinessWeight, fullLinesWeight;

	holeWeight = 6; //some values are more important than others, so different weights were given for them
	bumpinessWeight = 5; //(weights chosen after testing)

	fullLinesCount = board.getFullLinesCount();
	board.clearFullLines(); //We clear the lines before checking the holeCount and bumpiness, to keep those values updated
	holeCount = board.getHoleCount();
	bumpiness = board.getBumpinessLevel(fullLinesWeight); //fullLineWeight is determined by the tallest column's hight (as clearing lines is more important when there are tall sets of blocks on the board)

	board = temp; //The board is returned back to normal after all the changes
	//The score is calculated so that the bumpiness and holeCount will reduce the score, while the fullLines that are deleted will improve it
	return (float)(fullLinesCount * fullLinesWeight) - (bumpiness * (float)bumpinessWeight) - (float)(holeCount * holeWeight);
}

void Shape::glueShape() 
{
	int freeSpaceX, freeSpaceY;

	for (int i = 0; i < numOfBlocks; i++)
	{
		blockArr[i].getFreeSpaceXY(board, freeSpaceX, freeSpaceY); //We get the cords (in freeSpace) of the block in the array
		board.setFreeSpaceValue(ch, freeSpaceX, freeSpaceY); //...and update freeSpace accordingly
	}
}

void Shape::unGlueShape()
{
	int freeSpaceX, freeSpaceY;

	for (int i = 0; i < numOfBlocks; i++)
	{
		blockArr[i].getFreeSpaceXY(board, freeSpaceX, freeSpaceY); //We get the cords (in freeSpace) of the block in the array
		board.setFreeSpaceValue(' ', freeSpaceX, freeSpaceY); //...and update freeSpace accordingly
	}
}

void Shape::teleportToFloor()
{
	while (canShapeMoveOffset(0, 1))
		moveBy(0, 1);
}

void Shape::teleportToCeiling()
{
	int lowestY = blockArr[0].getY();

	for (int i = 1; i < numOfBlocks; i++)
		if (blockArr[i].getY() < lowestY)
			lowestY = blockArr[i].getY(); //We search for the lowestY in the shape...

	moveBy(0, board.getYStart() - lowestY + 1); //And move the shape up depending on that lowestY
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
	//coordinates (on-screen) of the "anchor" block, which is the main block of the shape (all the other block's coordinates are determined by the coordinates of the anchor block)
	int anchorX = board.getXStart() + board.getWidth() / 2; //the anchor block will always by in the middle of the board (on the X axis)
	int	anchorY = board.getYStart() + 1;

	switch (shape) //the empty positions array given to the function is set by the shape that was generated
	{
	case Shapes::I:
		divider = 2;//Another function is used to fill the positions array. The anchor cords will be set in the beginning, and the rest of the integers are offset cords (relative to the anchor itself)
		createCordsArr(positions, anchorX, anchorY, -1, 0, 1, 0, 2, 0); //For example here, The function receives the anchor cords, and the 3 non-anchor blocks are placed on the left of anchor, the right of anchor, and 2 places to the right of anchor. That creates an I shape.
		break;
	case Shapes::O:
	case Shapes::BOMB:
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




