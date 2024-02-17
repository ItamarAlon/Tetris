#include "bot.h"

Bot::Bot(Board& _board, char ch) : Shape(_board, ch)
{
}

void Bot::moveToPosition(const Position& bestPosition) //for testing
{
	moveBy(0, 1);
	while (getOrientation() != bestPosition.orientation)
		rotateShape((char)GameConfig::Lkeys::CLOCKWISE);
	int xBy = bestPosition.anchorX - getAnchorX();
	moveBy(xBy, 0);
	teleportToFloor();
	glueShape();
	if (board.checkFullLine()) //If the shape landed, the program checks if there are any full lines that were deleted.
		board.print(); //If there were, it prints the board again (which was updated)
	print();
}

void Bot::findBestPosition()
{
	int time = 0; //temp
	float score;
	int divider = getDivider();
	int spawnCords[8] = {};
	getSpawnCords(spawnCords);
	print();//tmp
	Sleep(1200);//tmp

	for (int i = 0; i < divider; i++)
	{
		while (canShapeMoveOffset(-1, 0))
			moveBy(-1, 0);

		while (true)
		{
			teleportToFloor();
			score = getPositionScore();
			updateBestPosition(score);

			teleportToCeiling();

			if (canShapeMoveOffset(1, 0))
			{
				moveBy(1, 0);
				print(); //tmp
			}
			else
			{
				changeShapePosition(spawnCords);
				print(); //tmp
				break;
			}
		}
		moveBy(0, 1);
		rotateShape((char)GameConfig::Lkeys::CLOCKWISE); //need to work for player 2 later...
		print(); //tmp
	}
}

float Bot::getPositionScore()
{
	const Board temp = board;
	glueShape();

	int holeCount, fullLinesCount;
	float bumpiness;
	int holeWeight, bumpinessWeight, fullLinesWeight;

	holeWeight = 6;
	bumpinessWeight = 3;

	fullLinesCount = getFullLinesCount();
	board.checkFullLine();
	holeCount = getHoleCount();
	bumpiness = getBumpinessLevel(fullLinesWeight);
	print(); //tmp
	board.print();
	Sleep(130); //tmp

	fullLinesWeight = pow(4, fullLinesWeight);
	board = temp;
	return (float)(fullLinesCount * fullLinesWeight) - (bumpiness * (float)bumpinessWeight) - (float)(holeCount * holeWeight);
}

void Bot::takeAction()
{ 
	char actionKey{};

	if (getOrientation() != bestPosition.orientation)
		rotateShape(' ');
	else if (getAnchorX() != bestPosition.anchorX)
		moveShapeLeftRight(' ');
	else
		moveShapeDown(); //Might delete
}

int Bot::getOffsetForLeftRight(char input)
{
	if (getAnchorX() < bestPosition.anchorX)
		return 1;
	else if (getAnchorX() > bestPosition.anchorX)
		return -1;
	return 0;
}

void Bot::updateBestPosition(float newScore)
{
	if (newScore > bestPosition.score)
	{
		getAnchorXY(bestPosition.anchorX, bestPosition.anchorY); 
		bestPosition.score = newScore;
		bestPosition.orientation = getOrientation();
	}
}

char Bot::getInputForAction(Action action)
{
	if (action == Action::LEFT)
	{
		if (playerNum == 1)
			return (char)GameConfig::Lkeys::LEFT;
		else
			return (char)GameConfig::Rkeys::LEFT;
	}
	else if (action == Action::RIGHT)
	{
		if (playerNum == 1)
			return (char)GameConfig::Lkeys::RIGHT;
		else
			return (char)GameConfig::Rkeys::RIGHT;
	}
	else if (action == Action::CLOCKWISE)
	{
		if (playerNum == 1)
			return (char)GameConfig::Lkeys::CLOCKWISE;
		else
			return (char)GameConfig::Rkeys::CLOCKWISE;
	}
	else if (action == Action::COUNTER_CLOCKWISE)
	{
		if (playerNum == 1)
			return (char)GameConfig::Lkeys::COUNTER_CLOCKWISE;
		else
			return (char)GameConfig::Rkeys::COUNTER_CLOCKWISE;
	}
}

int Bot::getNextOrientation(int key)
{
	return (getOrientation() + 1) % getDivider(); //Might make it smarted later
}

int Bot::getHoleCount()
{
	int holeCounter = 0, row;
	const int HEIGHT = board.getHeight();
	const int WIDTH = board.getWidth();

	for (int col = 1; col <= WIDTH; col++)
	{
		row = 1;
		while (!board.isSpaceTaken(col, row))
			row++;

		while (row < HEIGHT)
		{
			row++;
			if (!board.isSpaceTaken(col, row)) //Should work
				holeCounter++;
		}
	}
	
	return holeCounter;
}

float Bot::getBumpinessLevel(int& maxHeight)
{
	int heights[GameConfig::BOARD_WIDTH] = {};
	maxHeight = fillHeightsArr(heights);

	return standardDeviation(heights, GameConfig::BOARD_WIDTH);
}

int Bot::getFullLinesCount()
{
	int fullLineCounter = 0;

	for (int row = board.getHeight(); row > 0; row--)
		if (board.isLineFull(row))
			fullLineCounter++;

	return fullLineCounter;
}

int Bot::fillHeightsArr(int heights[])
{
	int maxHeight = heights[0] = board.getColHeight(1);

	for (int i = 1; i < GameConfig::BOARD_WIDTH; i++)
	{
		heights[i] = board.getColHeight(i + 1);
		if (heights[i] > maxHeight)
			maxHeight = heights[i];
	}
	return maxHeight;
}