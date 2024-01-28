#pragma once
#include "Libraries.h"
#include "Board.h"

class Board;

class Block
{
public:
	char ch;
    int x, y;
	Block(char _ch = ' ', int _x = 0, int _y = 0) : ch(_ch), x(_x), y(_y) {}
	void moveTo(int x, int y);
	void moveBy(int x, int y);
	void print();
	void setX(int x);
	void setY(int y);
	void setCords(int x, int y);
	void setChar(char ch);
	//void moveBlockDownBoard(Board board, int speed);
	void moveBlockLeftRight(char key);
	bool checkFreeSpaceOffset(int x, int y, Board& playerBoard);
	void getOffsetFromInput(char key, int& offsetX, int& offsetY);
	void getFreeSpaceXY(const Board& playerBoard, int& x, int& y);
};

