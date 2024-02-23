#pragma once
#include "shape.h"
//Class that handles the bomb.
class Bomb : public Shape
{
	Block& bomb = blockArr[0]; //Reference to the block of the bomb (as a bomb is made of 1 block only)
public:
	Bomb(Board& _board, char ch = '@');
	int explode();
	bool isBomb() const override;
	float getPositionScore() override; //Returns the score of the current position of the bomb (used by the computer)
private:
	void getExplosionRectangle(int& startX, int& startY, int& endX, int& endY); //returns the area of explosion
};

