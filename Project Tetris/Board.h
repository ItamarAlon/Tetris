#pragma once
#include "Libraries.h"
#include "gameConfig.h"

class GameConfig;
class Block;

class Board
{
public:
	const int X_START;
	const int Y_START;

	//const int WIDTH = GameConfig::BOARD_WIDTH;
	//const int HEIGHT = GameConfig::BOARD_HEIGHT;

	const int WIDTH = 10;
	const int HEIGHT = 20;

	const int X_END = X_START + WIDTH;
	const int Y_END = Y_START + HEIGHT;

	const int playerNum;

	Board(int x = 1, int y = 0, int _playerNum = 1) :X_START(x), Y_START(y), playerNum(_playerNum){}

	void print();
	//void moveBlockDownBoard(Block block, int speed);
};
