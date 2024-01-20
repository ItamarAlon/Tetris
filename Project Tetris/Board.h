#pragma once
#include "Libraries.h"
#include "gameConfig.h"

class GameConfig;
class Block;

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

class Board
{
public:
	const int X_START;
	const int Y_START;

	//const int WIDTH = GameConfig::BOARD_WIDTH;
	//const int HEIGHT = GameConfig::BOARD_HEIGHT;

	const int WIDTH = BOARD_WIDTH;
	const int HEIGHT = BOARD_HEIGHT;

	const int X_END = X_START + WIDTH;
	const int Y_END = Y_START + HEIGHT;

	//bool freeSpace[12][22] = {};
	//char freeSpace[12][22];
	char freeSpace[BOARD_HEIGHT + 2][BOARD_WIDTH + 2];

	const int playerNum;

	Board(int x = 30, int y = 0, int _playerNum = 1);
	//void resetBoard();
	void print();
	bool checkFreeSpaceCoordinates(int freeSpaceX, int freeSpaceY);
	void printFreeSpace(int x = 30, int y = 0);
	bool checkFullLine();
	void moveLinesDown(int line);
	//void moveBlockDownBoard(Block block, int speed);
};
