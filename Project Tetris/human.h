#pragma once
#include "player.h"
//Class for a human player
class Human : public Player
{
	const int playerNum = getPlayerNum();
public:
	Human(Board& _board, int _playerNum = 1);
	~Human();
	bool takeAction(char input) override; //Takes action for the player (depending on input from keyboard)
	bool botOrHuman() override;
private:
	int getNextOrientation(char input) override;
	int getOffsetForLeftRight(char input) override; //Returns whether the player moves left or right and the right offsetX for it.

};

