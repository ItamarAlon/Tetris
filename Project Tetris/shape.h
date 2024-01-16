#pragma once
#include "Libraries.h"
class Block;
class Board;

class Shape
{
	Block blockArr[4];
	Board board;

public:
	Shape(string string, const Board& _board, char ch = 254);
	void setShape(string string, char ch = 254);
	void print();
	void moveBy(int x, int y);
	bool moveShapeDown();
	void moveShapeLeftRight(int playerNum);

};

