#pragma once
#include "shape.h"
class Human : public Shape
{
	const int playerNum = board.getPlayerNum();
public:
	Human(Board& _board, char ch = -2);
	void takeAction();
	int getNextOrientation(int key);
	int getOffsetForLeftRight(char input);
};

