#pragma once
#include "shape.h"
class Player
{
	int playerNum;
	Shape& shape;

public:
	virtual int getNextOrientation(char input) = 0; //To player   //Returns the next orientation of the block (relative to the input from the keyboard)
	virtual int getOffsetForLeftRight(char input) = 0; //To player
	virtual bool botOrHuman() = 0; //To player
	virtual void takeAction(char input) = 0; //To player
};

