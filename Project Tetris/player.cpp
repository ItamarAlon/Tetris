#include "player.h"

Player::Player(Board& _board, int _playerNum) : board(_board), playerNum(_playerNum)
{
	setNewShape(false); //A new shape for the player is generated in the constructor. It was decided that the newShape will not be a bomb at the beginning
}

Player::~Player()
{
	delete shape;
}

int Player::getPlayerNum() const
{
    return playerNum;
}

void Player::setNewShape(bool allowBomb)
{
	bool makeBomb = oneInXChance(GameConfig::BOMB_CHANCE) && allowBomb;
	if (makeBomb)
		shape = new Bomb(board);
	else
		shape = new Shape(board);
}

void Player::updateTick()
{
	if (tick == nextActionTick)
		allowAction = true;

	tick = (tick + 1) % numOfTicks;
}

