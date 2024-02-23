#include "bomb.h"

Bomb::Bomb(Board& _board, char ch) : Shape(_board, ch)
{
	setBomb();
}

int Bomb::explode()
{
	int numOfDeleted = 0;
	int startX, startY, endX, endY;
	getExplosionRectangle(startX, startY, endX, endY); //We get the cords of the top left and down right of the explosion area

	for (int col = startX; col <= endX; col++)
		for (int row = startY; row <= endY; row++)
			if (board.getFreeSpaceValue(col, row) != ' ')
			{
				board.setFreeSpaceValue(' ', col, row); //Then, we override the value with ' ', to delete the block that was on the board
				numOfDeleted++; //We also count how many blocks were deleted
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
	bumpinessWeight = 5; //The weight of the holeCount and bumpiness (values were chosen after testing)

	bombedCount = explode(); //We explode the bomb and saves the number of blocks that were exploded
	holeCount = board.getHoleCount();
	bumpiness = board.getBumpinessLevel(bombedWeight); //the weight of the bombedCount gets higher when the columns get taller

	board = temp; //After exploding, we return the board back to the way it was
	//The scores is calculated by all the values. bumpiness and holeCount is negative so it reduced the score, while the number of blocks exploded improves the score
	return (float)(bombedCount * bombedWeight) - (bumpiness * (float)bumpinessWeight) - (float)(holeCount * holeWeight);
}

void Bomb::getExplosionRectangle(int& startX, int& startY, int& endX, int& endY)
{
	int x, y;
	bomb.getFreeSpaceXY(board, x, y);

	startX = x - GameConfig::BLAST_RADIUS; //the start of the rectangle is determined by the blast radius
	while (startX < 1) //But in case startX is out of the board, we increase it until it's inside the board.
		startX++;
	//Similar for other values
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
