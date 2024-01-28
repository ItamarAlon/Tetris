#pragma once
#include "Libraries.h"
#include "Board.h"

class Board;

class Block
{
	char ch;
    int x, y;
public:
	Block(char _ch = ' ', int _x = 0, int _y = 0) : ch(_ch), x(_x), y(_y) {}
	void moveTo(int x, int y);
	void moveBy(int x, int y);
	void print();
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	void setCords(int x, int y);
	void setChar(char ch);
	char getChar();
	void moveBlockLeftRight(char key);
	bool checkFreeSpaceOffset(int x, int y, Board& playerBoard);
	void getOffsetFromInput(char key, int& offsetX, int& offsetY);
	void getFreeSpaceXY(Board& playerBoard, int& x, int& y);
};

