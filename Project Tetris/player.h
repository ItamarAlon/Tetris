#pragma once
#include "shape.h"
#include "bomb.h"

//The player of the game
class Player
{
	const int playerNum;
protected:
	Shape* shape; //The shape the player is controlling
	Board& board; //The board he's playing on

	int tick = 0; //Number of ticks (which are gonna count up. Is used during the game)
	bool allowAction = true; //Checks if the player is allowed to make an action or not.
	int cooldown = 0; //The number of ticks the player has to "wait" until he can perform an action
	int nextActionTick = 0; //Once tick reaches that number, the player can perform an action
	int numOfTicks = 17; //Number of ticks in a single rotation

public:
	Player(Board& _board, int _playerNum = 1);
	virtual ~Player();
	virtual int getNextOrientation(char input) = 0; //Returns the next orientation of the shape
	virtual int getOffsetForLeftRight(char input) = 0; //Returns offsetX for the player to move Left/Right
	virtual bool botOrHuman() = 0; 
	virtual bool takeAction(char input) = 0; //Performs an action

	int getPlayerNum() const;
	virtual void setNewShape(bool allowBomb = true); //Sets up a new shape for the player
	friend class Game; //Because class game uses the "shape" and "board" variables all the time, it was decided that it will have access to it's variables.

protected:
	void updateTick();
};

