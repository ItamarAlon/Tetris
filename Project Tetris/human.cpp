#include "human.h"

Human::Human(Board& _board, int _playerNum) : Player(_board, _playerNum)
{
}

Human::~Human()
{
}

bool Human::takeAction(char input)
{
	if (!allowAction)
		return false;

	input = getLowerCase(input);
	int nextOrientation = getNextOrientation(input);
	int offSetX = getOffsetForLeftRight(input);

	if (getPlayerNum() == 1)
		switch (input)
		{
		case (char)GameConfig::Lkeys::LEFT:
		case (char)GameConfig::Lkeys::RIGHT:
			shape->moveShapeLeftRight(offSetX); //Using a function in case a shape needs to move Left/Right
			cooldown = (int)GameConfig::Cooldowns::LEFT_RIGHT;
			allowAction = false;
			break;
		case (char)GameConfig::Lkeys::DOWN:
			shape->moveShapeDown(); //If DOWN was pressed, we need to increase the shape's speed. So we move it down by 1 to mimik the feeling of increased speed
			cooldown = (int)GameConfig::Cooldowns::DOWN;
			allowAction = false;
			break;
		case (char)GameConfig::Lkeys::CLOCKWISE:
		case (char)GameConfig::Lkeys::COUNTER_CLOCKWISE:
			shape->rotateShape(nextOrientation);
			shape->print();
			cooldown = (int)GameConfig::Cooldowns::ROTATE;
			allowAction = false;
			break;
		default:
			break;
		}
	else
		switch (input)
		{
		case (char)GameConfig::Rkeys::LEFT:
		case (char)GameConfig::Rkeys::RIGHT:
			shape->moveShapeLeftRight(offSetX); //Using a function in case a shape needs to move Left/Right
			cooldown = (int)GameConfig::Cooldowns::LEFT_RIGHT;
			allowAction = false;
			break;
		case (char)GameConfig::Rkeys::DOWN:
			shape->moveShapeDown(); //If DOWN was pressed, we need to increase the shape's speed. So we move it down by 1 to mimik the feeling of increased speed
			cooldown = (int)GameConfig::Cooldowns::DOWN;
			allowAction = false;
			break;
		case (char)GameConfig::Rkeys::CLOCKWISE:
		case (char)GameConfig::Rkeys::COUNTER_CLOCKWISE:
			shape->rotateShape(nextOrientation);
			shape->print();
			cooldown = (int)GameConfig::Cooldowns::ROTATE;
			allowAction = false;
			break;
		default:
			break;
		}

	if (!allowAction)
	{
		nextActionTick = (tick + cooldown) % numOfTicks;
		return true;
	}
	return false;
}

int Human::getNextOrientation(char input)
{
	int nextOrientation;
	char clockwise;

	if (getPlayerNum() == 1)
		clockwise = (char)GameConfig::Lkeys::CLOCKWISE;
	else
		clockwise = (char)GameConfig::Rkeys::CLOCKWISE;

	if (input == clockwise)
		nextOrientation = (shape->getOrientation() + 1) % shape->getDivider(); //If rotating clockwise was chosen, we go to the nextOrientation (which returns to 0 after going through all orientations, which is why module is used
	else
		nextOrientation = shape->getOrientation() - 1; //Otherwise, orientation goes down by 1, which can cause it to turn -1 (which is illegal).

	if (nextOrientation == -1) //so if the orientation is -1, we change it to the last orientation
		nextOrientation = shape->getDivider() - 1;

	return nextOrientation;
}

int Human::getOffsetForLeftRight(char input)
{
	char left, right;
	if (getPlayerNum() == 1)
	{
		left = (char)GameConfig::Lkeys::LEFT;
		right = (char)GameConfig::Lkeys::RIGHT;
	}
	else
	{
		left = (char)GameConfig::Rkeys::LEFT;
		right = (char)GameConfig::Rkeys::RIGHT;
	}

	if (input == left)
		return -1;  //If the input from the keyboard is left, than the shape moves 1 place to the left (or, the x cord of the block goes down by 1)
	if (input == right)
		return 1; //Else, the shape moves 1 place to the right
	return 0;
}

bool Human::botOrHuman()
{
	return (bool)GameConfig::Type::HUMAN;
}

