#include "bomb.h"

Bomb::Bomb(Board& _board, char ch) : Bot(_board, ch)
{
	turnToBomb();
}

void Bomb::moveBy(int x, int y) //rewrite
{
	blockArr[0].moveBy(x, y);
}

bool Bomb::canShapeMoveOffset(int offsetX, int offsetY) //rewrite
{
	return !blockArr[0].isSpaceTakenOffset(offsetX, offsetY, board);
}

void Bomb::teleportToCeiling() //rewrite
{
	int x = blockArr[0].getX();
	int y = board.getYStart() + 1;

	blockArr[0].moveTo(x, y);
}