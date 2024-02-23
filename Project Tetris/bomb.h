#pragma once
#include "shape.h"
class Bomb : public Shape
{
	Block& bomb = blockArr[0];
public:
	Bomb(Board& _board, char ch = '@');
	int explode();
	bool isBomb() const override;
	float getPositionScore() override;
private:
	void getExplosionRectangle(int& startX, int& startY, int& endX, int& endY);
};

