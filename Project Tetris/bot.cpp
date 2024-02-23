#include "bot.h"

Bot::Bot(Board& _board, GameConfig::Bot_Level _level, int _playerNum) : Player(_board, _playerNum), level(_level)
{
	updatePositions();
}

Bot::~Bot()
{
}
//The function doesn't actually use the input. It's only there because it's a virtual function
bool Bot::takeAction(char input)
{ 
	if (!allowAction)
		return false;

	int nextOrientation = getNextOrientation(' ');
	int offSetX = getOffsetForLeftRight(' ');

	if (shape->getOrientation() != goToPosition.orientation)
	{
		shape->rotateShape(nextOrientation); //If the shape is not in the right orientation, we rotate it
		shape->print();
		cooldown = (int)GameConfig::Cooldowns::ROTATE; //cooldown until shape can be rotated again
	}
	else if (offSetX != 0)
	{
		shape->moveShapeLeftRight(offSetX);
		cooldown = (int)GameConfig::Cooldowns::LEFT_RIGHT;
	}
	else
	{
		shape->moveShapeDown(); //When the shape is under the position it's suppose to go to, the computer increases the shape's speed
		cooldown = (int)GameConfig::Cooldowns::DOWN;
	}

	allowAction = false; //after action was performed, the computer will have to wait
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

	if (level == GameConfig::Bot_Level::GOOD && oneInXChance((int)GameConfig::Bot_Accuracy::GOOD))
		goToPosition = worstPosition; //If the bot level is low enough, it has a chance to go to the worst position instead of the best
	else if (level == GameConfig::Bot_Level::NOVICE && oneInXChance((int)GameConfig::Bot_Accuracy::NOVICE))
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
	return (shape->getOrientation() + 1) % shape->getDivider();
}


