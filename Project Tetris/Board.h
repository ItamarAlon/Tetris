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

	const int WIDTH = 11;
	const int HEIGHT = 20;

	const int X_END = X_START + WIDTH;
	const int Y_END = Y_START + HEIGHT;

	bool freeSpace[12][22] = {};
	//char freeSpace[12][22];

	const int playerNum;

	Board(int x = 30, int y = 0, int _playerNum = 1);
	//void resetBoard();
	void print();
	bool checkFreeSpaceCoordinates(int freeSpaceX, int freeSpaceY);
	void printFreeSpace();
	//void moveBlockDownBoard(Block block, int speed);
};
