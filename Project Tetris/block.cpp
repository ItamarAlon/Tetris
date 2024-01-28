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
void Block::print()
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

int Block::getX()
{
	return x;
}

int Block::getY()
{
	return y;
}

void Block::setChar(char ch)
{
	this->ch = ch;
}

char Block::getChar()
{
	return ch;
}

void Block::setCords(int x, int y)
{
	setX(x);
	setY(y);
}

void Block::moveBlockLeftRight(char key)
{
	if (key == (char)GameConfig::Lkeys::LEFT || key == (char)GameConfig::Rkeys::LEFT)
		moveBy(-1, 0);
	else if (key == (char)GameConfig::Lkeys::RIGHT || key == (char)GameConfig::Rkeys::RIGHT)
		moveBy(1, 0);
}

bool Block::isSpaceTakenOffset(int offsetX, int offsetY, Board& playerBoard) 
{
	int freeSpaceX, freeSpaceY;
	getFreeSpaceXY(playerBoard, freeSpaceX, freeSpaceY); //updates freeSpaceX and freeSpaceY to represnt the cords of the block in the freeSpace array.

	if (playerBoard.isSpaceTaken(freeSpaceX + offsetX, freeSpaceY) || playerBoard.isSpaceTaken(freeSpaceX, freeSpaceY + offsetY)) 
		return true; //If the space on board placed offsetX and offsetY values from the block is taken, return true.
	return false;
}

void Block::getOffsetFromInput(char key, int& offsetX, int& offsetY)
{
	if (key == (char)GameConfig::Lkeys::LEFT || key == (char)GameConfig::Rkeys::LEFT)
		offsetX = -1;  //If the input from the keyboard is left, than the block moves 1 place to the left (or, the x cord of the block goes down by 1)
	if (key == (char)GameConfig::Lkeys::RIGHT || key == (char)GameConfig::Rkeys::RIGHT)
		offsetX = 1; 
	offsetY = 0; //Either way, the block doesn't change it's height.
}

void Block::getFreeSpaceXY(Board& playerBoard, int& x, int& y)
{
	x = this->x - playerBoard.getXStart(); //The cords of a block in the freeSpace array is calculated by taking the cords of the block on-screen, and removing the Boards' cords on-screen.
	y = this->y - playerBoard.getYStart();
}


