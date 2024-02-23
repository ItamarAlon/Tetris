#include "bomb.h"

Bomb::Bomb(Board& _board, char ch) : Shape(_board, ch)
{
	setBomb();
}

int Bomb::explode()
{
	int numOfDeleted = 0;
	int startX, startY, endX, endY;
	getExplosionRectangle(startX, startY, endX, endY);

	for (int col = startX; col <= endX; col++)
		for (int row = startY; row <= endY; row++)
			if (board.getFreeSpaceValue(col, row) != ' ')
			{
				board.setFreeSpaceValue(' ', col, row);
				numOfDeleted++;
			}
	return numOfDeleted;
}

bool Bomb::isBomb() const
{
	return true;
}

float Bomb::getPositionScore()
{
	const Board temp = board;

	int holeCount, bombedCount;
	float bumpiness;
	int holeWeight, bumpinessWeight, bombedWeight;

	holeWeight = 6;
	bumpinessWeight = 5;

	bombedCount = explode();
	holeCount = board.getHoleCount();
	bumpiness = board.getBumpinessLevel(bombedWeight);

	bombedWeight += 0;
	board = temp;
	return (float)(bombedCount * bombedWeight) - (bumpiness * (float)bumpinessWeight) - (float)(holeCount * holeWeight);
}

void Bomb::getExplosionRectangle(int& startX, int& startY, int& endX, int& endY)
{
	int x, y;
	bomb.getFreeSpaceXY(board, x, y);

	startX = x - GameConfig::BLAST_RADIUS;
	while (startX < 1)
		startX++;

	startY = y - GameConfig::BLAST_RADIUS;
	while (startY < 1)
		startY++;

	endX = x + GameConfig::BLAST_RADIUS;
	while (endX > board.getWidth())
		endX--;

	endY = y + GameConfig::BLAST_RADIUS;
	while (endY > board.getHeight())
		endY--;
}
