#pragma once
#include "shape.h"
class Human : public Shape
{
	const int playerNum = board.getPlayerNum();
public:
	Human(Board& _board, char ch = -2);
	void takeAction(char input) override;
	bool botOrHuman() override;
private:
	int getNextOrientation(int key) override;
	int getOffsetForLeftRight(char input) override;

};

