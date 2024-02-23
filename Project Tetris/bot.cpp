#include "bot.h"

Bot::Bot(Board& _board, int _playerNum) : Player(_board, _playerNum)
{
	updateBestPosition();
}

void Bot::takeAction(char input)
{ 
	int nextOrientation = getNextOrientation(' ');
	int offSetX = getOffsetForLeftRight(' ');

	if (shape->getOrientation() != bestPosition.orientation)
	{
		shape->rotateShape(nextOrientation);
		shape->print();
	}
	else if (shape->getAnchorX() != bestPosition.anchorX)
		shape->moveShapeLeftRight(offSetX);
	else
		shape->moveShapeDown();
}

int Bot::getOffsetForLeftRight(char input)
{
	if (shape->getAnchorX() < bestPosition.anchorX)
		return 1;
	else if (shape->getAnchorX() > bestPosition.anchorX)
		return -1;
	return 0;
}

bool Bot::botOrHuman()
{
	return (bool)GameConfig::Type::BOT;
}

void Bot::updateBestPosition()
{
	shape->findBestPosition(bestPosition);
}

void Bot::setNewShape(bool allowBomb)
{
	Player::setNewShape(allowBomb);
	updateBestPosition();
}

int Bot::getNextOrientation(char input)
{
	return (shape->getOrientation() + 1) % shape->getDivider(); //Might make it smarter later
}