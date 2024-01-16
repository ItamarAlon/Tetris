#include "block.h"
#include "Libraries.h"

void Block::moveTo(int x, int y)
{
	gotoxy(this->x, this->y);
	cout << " ";
	//yeleshara
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

void Block::setChar(char ch)
{
	this->ch = ch;
}

//void Block::moveBlockDownBoard(Board board, int speed)
//{
//	//block.setCords(X_START + WIDTH / 2, Y_START + 1);
//
//	for (int i = 0; i < board.HEIGHT - 1; i++)
//	{
//		moveBlockLeftRight(board.playerNum);
//		print();
//		Sleep(speed);
//		moveBy(0, 1);
//		print();
//	}
//}

void Block::setCords(int x, int y)
{
	setX(x);
	setY(y);
}

void Block::moveBlockLeftRight(char key, int playerNum)
{
	if (playerNum == 1)
	{
		if (key == (char)GameConfig::Lkeys::LEFT)
			moveBy(-1, 0);
		else if (key == (char)GameConfig::Lkeys::RIGHT)
			moveBy(1, 0);
	}
	else if (playerNum == 2)
	{
		if (key == (char)GameConfig::Rkeys::LEFT)
			moveBy(-1, 0);
		else if (key == (char)GameConfig::Rkeys::RIGHT)
			moveBy(1, 0);
	}
}

bool Block::checkFreeSpace(int offsetX, int offsetY, Board& playerBoard) 
{
	int freeSpaceX = x - playerBoard.X_START;
	int freeSpaceY = y - playerBoard.Y_START;

	if (playerBoard.freeSpace[offsetX + freeSpaceX][freeSpaceY] == false || playerBoard.freeSpace[freeSpaceX][offsetY + freeSpaceY] == false)
		return true;
	return false;
}

void Block::getOffsetFromInput(char key, int& offsetX, int& offsetY)
{
	if (key == (char)GameConfig::Lkeys::LEFT)
		offsetX = -1; offsetY = 0;
	if (key == (char)GameConfig::Lkeys::RIGHT)
		offsetX = 1; offsetY = 0;
}


