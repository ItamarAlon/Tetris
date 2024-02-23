#pragma once
#include "player.h"
class Human : public Player
{
	const int playerNum = board.getPlayerNum();
public:
	Human(Board& _board, int _playerNum = 1);
	~Human();
	bool takeAction(char input) override;
	bool botOrHuman() override;
private:
	int getNextOrientation(char input) override;
	int getOffsetForLeftRight(char input) override;

};

