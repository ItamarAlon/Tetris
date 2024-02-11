#include "computer.h"

//Computer::Computer(int x, int y, int _playerNum, const Shape& _shape) : Board(x, y, _playerNum), shape(_shape)
//{
//}

Computer::Computer(Board& _board, char ch) : Shape(_board, ch)
{
}

void Computer::findBestPosition(Position& bestPosition)
{
	int score;
	while (canShapeMove(-1, 0))
	{
		moveBy(-1, 0);
		Sleep(300); //temp
	}

	bool keepScanning = true;
	while (keepScanning)
	{
		teleportToFloor();
		score = getPositionScore();
		updatePosition(bestPosition, score);

		Sleep(300); //temp
		while (!canShapeMove(1, 0)) //What happens when it's blocked
		{
			if (getAnchorY() > board.getYStart() + 1)
				moveBy(0, -1);
			else
			{
				keepScanning = false;
				break;
			}
			Sleep(300); //temp
		}
		if (keepScanning)
			moveBy(1, 0);
		Sleep(300); //temp
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
		getAnchorXY(bestPosition.anchorX, bestPosition.anchorY);
		bestPosition.score = score;
		bestPosition.orientation = getOrientation();
	}
}
