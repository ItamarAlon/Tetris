#pragma once
#include "general.h"
#include "gameConfig.h"

class GameConfig;
class Block;

//Class that handles the board that the game is gonna be played on.
class Board
{
    const int X_START;
	const int Y_START; // coordinates of the top-right corner of the board

	const int WIDTH = GameConfig::BOARD_WIDTH;
	const int HEIGHT = GameConfig::BOARD_HEIGHT;

	//2D array that saves the blocks that stay on screen, as well as the border itself. Used to tell if a space on the board is taken or not, and where the tetrominoes can move on-screen.
	char freeSpace[GameConfig::BOARD_HEIGHT + 2][GameConfig::BOARD_WIDTH + 2]; 
	bool isFull = false; //Tells if the board is full or not.

public:
	Board(int x, int y);
	Board(const Board& newBoard);
	Board& operator=(const Board& from);
	void resetBoard(); //Function that returns the board to it's default form at the start of the game.
	bool isSpaceTaken(int freeSpaceX, int freeSpaceY) const; //Checks if certain cords (in the freeSpace array) are taken.
	void print() const;
	int getXStart() const;
	int getYStart() const;
	int getWidth() const;
	int getHeight() const;
	int getColumnHeight(int col) const;
	bool clearFullLines(); //Checks if there is a line full of blocks on the board, and deletes it if there is one, while moving all lines above it down.
	bool isLineFull(int line); //Receives a line in the board and checks if it's full or not
	void updateIsFull(); 
	bool isBoardFull() const;
	char getFreeSpaceValue(int x, int y) const; //Returns the value of a certain item in the freeSpace array
	void setFreeSpaceValue(char value, int x, int y); //Sets the value of a certain item in the freeSpace array
	void convertXYToFreeSpaceXY(int x, int y, int& freeSpaceX, int& freeSpaceY) const;

	int getHoleCount(); //Counts how many holes there are on the board. Hole here is defined as a space with a block placed above it (in the same column)
	float getBumpinessLevel(int& maxHeight); //Returns how uneven the board is
	int getFullLinesCount(); //Returns how many full lines are there on the board
private:
	void moveLinesDown(int line); //Moves all lines down by 1.
	int fillHeightsArr(int heights[]); //Fills an array that represent the height of every column (the highest block in the column). It also returns the height of the tallest column.
};
