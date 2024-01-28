#include "block.h"
#include "Libraries.h"

void Block::moveTo(int x, int y)
{
	gotoxy(this->x, this->y);
	cout << " ";
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

void Block::moveBlockLeftRight(char key)
{
	if (key == (char)GameConfig::P1keys::LEFT || key == (char)GameConfig::P2keys::LEFT)
		moveBy(-1, 0);
	else if (key == (char)GameConfig::P1keys::RIGHT || key == (char)GameConfig::P2keys::RIGHT)
		moveBy(1, 0);
}

bool Block::checkFreeSpaceOffset(int offsetX, int offsetY, Board& playerBoard) 
{
	int freeSpaceX, freeSpaceY;
	getFreeSpaceXY(playerBoard, freeSpaceX, freeSpaceY);

	if (playerBoard.isSpaceTaken(freeSpaceX + offsetX, freeSpaceY) || playerBoard.isSpaceTaken(freeSpaceX, freeSpaceY + offsetY))
		return true;
	return false;

	//if (playerBoard.getFreeSpaceItem(freeSpaceX + offsetX, freeSpaceY) != ' ' || playerBoard.getFreeSpaceItem(freeSpaceX, freeSpaceY + offsetY) != ' ')
	//	return true;
	//return false;

}

void Block::getOffsetFromInput(char key, int& offsetX, int& offsetY)
{
	if (key == (char)GameConfig::P1keys::LEFT || key == (char)GameConfig::P2keys::LEFT)
		offsetX = -1; 
	if (key == (char)GameConfig::P1keys::RIGHT || key == (char)GameConfig::P2keys::RIGHT)
		offsetX = 1; 
	offsetY = 0;
}

void Block::getFreeSpaceXY(Board& playerBoard, int& x, int& y)
{
	x = this->x - playerBoard.getXStart();
	y = this->y - playerBoard.getYStart();
}


