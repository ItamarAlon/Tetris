#include "computer.h"

//Computer::Computer(int x, int y, int _playerNum, const Shape& _shape) : Board(x, y, _playerNum), shape(_shape)
//{
//}


Computer::Computer(Board& _board, char ch) : Shape(_board, ch)
{
}

void Computer::findBestPosition(Position& bestPosition)
{
	int score, divider = getDivider();
	bool canMoveRight = true;
	int spawnCords[8] = {};
	getSpawnCords(spawnCords);

	for (int i = 0; i < divider; i++)
	{
		while (canShapeMove(-1, 0))
		{
			moveBy(-1, 0);
			Sleep(300); //temp
		}

		while (canMoveRight)
		{
			teleportToFloor();
			score = getPositionScore();
			updateBestPosition(bestPosition, score);

			Sleep(300); //temp
			teleportToCeiling();
			Sleep(300); //temp

			if (canShapeMove(1, 0))
				moveBy(1, 0);
			else
			{
				changeShapePosition(spawnCords);
				print(); //temp
				canMoveRight = false;
				break;
			}
		}
		moveBy(0, 1);
		rotateShape((char)GameConfig::Lkeys::CLOCKWISE); //need to work for player 2 later...
		canMoveRight = true;
	}
}

float Computer::getPositionScore()
{
	glueShape();
	int holeCount, fullLinesCount;
	float bumpiness;
	int holeWeight, bumpinessWeight, fullLinesWeight;
	holeWeight = bumpinessWeight = fullLinesWeight = 1; //For now...

	holeCount = getHoleCount();
	bumpiness = getBumpinessLevel();
	fullLinesCount = getFullLinesCount();

	unGlueShape();
	return (fullLinesCount * fullLinesWeight) - (bumpiness * bumpinessWeight) - (holeCount * holeWeight);
}

void Computer::updateBestPosition(Position& bestPosition, int score)
{
	if (score > bestPosition.score)
	{
		getAnchorXY(bestPosition.anchorX, bestPosition.anchorY); //Might change to FreeSpace cords instead
		bestPosition.score = score;
		bestPosition.orientation = getOrientation();
	}
}

int Computer::getHoleCount()
{
	int holeCounter = 0, row;
	const int HEIGHT = board.getHeight();
	const int WIDTH = board.getWidth();

	for (int col = 1; col <= WIDTH; col++)
	{
		row = 1;
		while (board.getFreeSpaceValue(col, row) == ' ')
			row++;

		while (row < HEIGHT)
		{
			row++;
			if (board.getFreeSpaceValue(col, row) == ' ') //Should work
				holeCounter++;
		}
	}
	
	return holeCounter;
}

double Computer::getBumpinessLevel()
{
	int heights[GameConfig::BOARD_WIDTH] = {};

	for (int col = 1; col <= GameConfig::BOARD_WIDTH; col++)
		heights[col - 1] = board.getColHeight(col);

	return standardDeviation(heights, GameConfig::BOARD_WIDTH);
}

int Computer::getFullLinesCount()
{
	int fullLineCounter = 0;

	for (int row = board.getHeight(); row > 0; row--)
		if (board.isLineFull(row))
			fullLineCounter++;

	return fullLineCounter;
}