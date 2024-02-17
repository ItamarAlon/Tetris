#include "human.h"

Human::Human(Board& _board, char ch) : Shape(_board, ch)
{
}

void Human::takeAction()
{
	if (_kbhit())
	{
		char key = _getch(); //If a key was pressed, we save it

		if (playerNum == 1)
		{
			switch (key)
			{
			case (char)GameConfig::Lkeys::LEFT:
			case (char)GameConfig::Lkeys::RIGHT:
				moveShapeLeftRight(key); //Using a function in case a shape needs to move Left/Right
				break;
			case (char)GameConfig::Lkeys::LEFT - 32:
			case (char)GameConfig::Lkeys::RIGHT - 32:
				moveShapeLeftRight(key + 32); //In case the uppercase version of the key was received..
				break;
			case (char)GameConfig::Lkeys::DOWN:
			case (char)GameConfig::Lkeys::DOWN - 32:
				moveShapeDown(); //If DOWN was pressed, we need to increase the shape's speed. So we move it down by 1 to mimik the feeling of increased speed
				break;
			case (char)GameConfig::Lkeys::CLOCKWISE:
			case (char)GameConfig::Lkeys::COUNTER_CLOCKWISE:
				rotateShape(key);
				break;
			case (char)GameConfig::Lkeys::CLOCKWISE - 32:
			case (char)GameConfig::Lkeys::COUNTER_CLOCKWISE - 32:
				rotateShape(key + 32);
				break;
			default:
				break;
			}
		}
		else
		{
			switch (key)
			{
			case (char)GameConfig::Rkeys::LEFT:
			case (char)GameConfig::Rkeys::RIGHT:
				moveShapeLeftRight(key); //Using a function in case a shape needs to move Left/Right
				break;
			case (char)GameConfig::Rkeys::LEFT - 32:
			case (char)GameConfig::Rkeys::RIGHT - 32:
				moveShapeLeftRight(key + 32); //In case the uppercase version of the key was received..
				break;
			case (char)GameConfig::Rkeys::DOWN:
			case (char)GameConfig::Rkeys::DOWN - 32:
				moveShapeDown(); //If DOWN was pressed, we need to increase the shape's speed. So we move it down by 1 to mimik the feeling of increased speed
				break;
			case (char)GameConfig::Rkeys::CLOCKWISE:
			case (char)GameConfig::Rkeys::COUNTER_CLOCKWISE:
				rotateShape(key);
				break;
			case (char)GameConfig::Rkeys::CLOCKWISE - 32:
			case (char)GameConfig::Rkeys::COUNTER_CLOCKWISE - 32:
				rotateShape(key + 32);
				break;
			default:
				break;
			}
		}
	}
}

int Human::getNextOrientation(int key)
{
	int nextOrientation;
	char clockwise;

	if (playerNum == 1)
		clockwise = (char)GameConfig::Lkeys::CLOCKWISE;
	else
		clockwise = (char)GameConfig::Rkeys::CLOCKWISE;

	if (key == clockwise)
		nextOrientation = (getOrientation() + 1) % getDivider(); //If rotating clockwise was chosen, we go to the nextOrientation (which returns to 0 after going through all orientations, which is why module is used
	else
		nextOrientation = getOrientation() - 1; //Otherwise, orientation goes down by 1, which can cause it to turn -1 (which is illegal).

	if (nextOrientation == -1) //so if the orientation is -1, we change it to the last orientation
		nextOrientation = getDivider() - 1;

	return nextOrientation;
}

int Human::getOffsetForLeftRight(char input)
{
	char left, right;
	if (board.getPlayerNum() == 1)
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

