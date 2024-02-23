#pragma once
#include "shape.h"
#include "bomb.h"
//class Bomb;
class Player
{
	const int playerNum;

protected:
	Shape* shape;
	Board& board;

public:
	Player(Board& _board, int _playerNum = 1);
	~Player();
	virtual int getNextOrientation(char input) = 0; //To player   //Returns the next orientation of the block (relative to the input from the keyboard)
	virtual int getOffsetForLeftRight(char input) = 0; //To player
	virtual bool botOrHuman() = 0; //To player
	virtual void takeAction(char input) = 0; //To player

	int getPlayerNum() const;
	void printBoard(); //Will probably delete later
	virtual void setNewShape(bool allowBomb = true);
	friend class Game;
};

