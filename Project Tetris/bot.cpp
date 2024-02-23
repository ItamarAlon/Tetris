#include "bot.h"

Bot::Bot(Board& _board, GameConfig::Bot_Level _level, int _playerNum) : Player(_board, _playerNum), level(_level)
{
	updatePositions();
}

Bot::~Bot()
{
}

bool Bot::takeAction(char input)
{ 
	if (!allowAction)
		return false;

	int nextOrientation = getNextOrientation(' ');
	int offSetX = getOffsetForLeftRight(' ');

	if (shape->getOrientation() != goToPosition.orientation)
	{
		shape->rotateShape(nextOrientation);
		shape->print();
		cooldown = (int)GameConfig::Cooldowns::ROTATE;
	}
	else if (offSetX != 0)
	{
		shape->moveShapeLeftRight(offSetX);
		cooldown = (int)GameConfig::Cooldowns::LEFT_RIGHT;
	}
	else
	{
		shape->moveShapeDown();
		cooldown = (int)GameConfig::Cooldowns::DOWN;
	}

	allowAction = false;
	nextActionTick = (tick + cooldown) % numOfTicks;
	return true;
}

int Bot::getOffsetForLeftRight(char input)
{
	if (shape->getAnchorX() < goToPosition.anchorX)
		return 1;
	else if (shape->getAnchorX() > goToPosition.anchorX)
		return -1;
	return 0;
}

bool Bot::botOrHuman()
{
	return (bool)GameConfig::Type::BOT;
}

void Bot::updatePositions()
{
	shape->findBestAndWorstPosition(bestPosition, worstPosition);

	if ((level == GameConfig::Bot_Level::GOOD && oneInXChance(40)) || (level == GameConfig::Bot_Level::NOVICE && oneInXChance(10)))
		goToPosition = worstPosition;
	else
		goToPosition = bestPosition;
}

void Bot::setNewShape(bool allowBomb)
{
	Player::setNewShape(allowBomb);
	updatePositions();
}

int Bot::getNextOrientation(char input)
{
	return (shape->getOrientation() + 1) % shape->getDivider(); //Might make it smarter later
}

void Bot::messUpPosition()
{
	int leftDistance = shape->getDistanceFromBorder(GameConfig::Direction::LEFT);
	int rightDistance = shape->getDistanceFromBorder(GameConfig::Direction::RIGHT);

	int randomOffset = generateNumberInInterval(-leftDistance, rightDistance);
	bestPosition.anchorX += randomOffset;
}

