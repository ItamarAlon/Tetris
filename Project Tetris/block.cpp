#include "block.h"

Block::Block(char _ch, int _x, int _y) : ch(_ch), x(_x), y(_y)
{
}

void Block::moveTo(int x, int y)
{
	gotoxy(this->x, this->y);
	cout << " "; //Goes to the block's current locations, deletes it's values, and set a new location for the block
	setCords(x, y);
}
void Block::moveBy(int x, int y)
{
	moveTo(this->x + x, this->y + y);
}
void Block::print() const
{
	gotoxy(x, y);
	cout << ch;
}

void Block::setX(int x)
{
	this->x = x;
}

void Block::setY(int y)
{
	this->y = y;
}

int Block::getX() const
{
	return x;
}

int Block::getY() const
{
	return y;
}

void Block::setChar(char ch)
{
	this->ch = ch;
}

char Block::getChar() const
{
	return ch;
}

void Block::setCords(int x, int y)
{
	setX(x);
	setY(y);
}

bool Block::isSpaceTakenOffset(int offsetX, int offsetY, const Board& playerBoard) const 
{
	int freeSpaceX, freeSpaceY;
	getFreeSpaceXY(playerBoard, freeSpaceX, freeSpaceY); //updates freeSpaceX and freeSpaceY to represnt the cords of the block in the freeSpace array.
	if (playerBoard.isSpaceTaken(freeSpaceX + offsetX, freeSpaceY) || playerBoard.isSpaceTaken(freeSpaceX, freeSpaceY + offsetY)) 
		return true; //If the space on board placed offsetX and offsetY values from the block is taken, return true.
	return false;
}

void Block::getFreeSpaceXY(const Board& playerBoard, int& freeSpaceX, int& freeSpaceY) const
{
	playerBoard.convertXYToFreeSpaceXY(this->x, this->y, freeSpaceX, freeSpaceY);
}


