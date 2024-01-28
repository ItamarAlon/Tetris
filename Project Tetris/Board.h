#pragma once
#include "Libraries.h"
#include "gameConfig.h"

class GameConfig;
class Block;

class Board
{
    const int X_START;
	const int Y_START;

	const int WIDTH = GameConfig::BOARD_WIDTH;
	const int HEIGHT = GameConfig::BOARD_HEIGHT;

	char freeSpace[GameConfig::BOARD_HEIGHT + 2][GameConfig::BOARD_WIDTH + 2];

	const int playerNum;
	bool isFull = false;
public:
	bool isLineDeleted = false;

	Board(int x, int y, int _playerNum = 1);
	void resetBoard();
	bool isSpaceTaken(int freeSpaceX, int freeSpaceY);
	void print();
	int getXStart();
	int getYStart();
	int getWidth();
	int getHeight();
	void checkFullLine();
	void moveLinesDown(int line);
	void updateIsFull(); 
	bool isBoardFull();
	char getFreeSpaceItem(int x, int y);
	void setFreeSpaceItem(char value, int x, int y);
	int getPlayerNum();
};
