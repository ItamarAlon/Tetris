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
			updatePosition(bestPosition, score);

			Sleep(300); //temp
			while (!canShapeMove(1, 0)) //What happens when it's blocked
			{
				if (canShapeMove(0, -1)) //Might need to change later, because can be problematic for certain situations
					moveBy(0, -1);
				else
				{
					getSpawnCords(spawnCords);
					changeShapePosition(spawnCords);
					print(); //temp
					canMoveRight = false;
					break;
				}
				Sleep(300); //temp
			}
			if (canMoveRight)
				moveBy(1, 0);
		}
		moveBy(0, 1);
		rotateShape((char)GameConfig::Lkeys::CLOCKWISE); //need to work for player 2 later...
		canMoveRight = true;
	}
}

int Computer::getPositionScore() const
{
	return 0;
}

void Computer::updatePosition(Position& bestPosition, int score)
{
	if (score > bestPosition.score)
	{
		getAnchorXY(bestPosition.anchorX, bestPosition.anchorY); //Might change to FreeSpace cords instead
		bestPosition.score = score;
		bestPosition.orientation = getOrientation();
	}
}
