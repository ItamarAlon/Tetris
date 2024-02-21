#pragma once
#include "bot.h"
class Bomb : public Bot
{
	Bomb(Board& _board, char ch = '@');
	void moveBy(int x, int y);
	bool canShapeMoveOffset(int offsetX, int offsetY);
	void teleportToCeiling();
};

