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

	const int playerNum;
	bool isFull = false; //Tells if the board is full or not.
public:
	Board(int x, int y, int _playerNum);
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
	bool checkFullLine(); //Checks if there is a line full of blocks on the board, and deletes it if there is one, while moving all lines above it down.
	bool isLineFull(int line);
	void updateIsFull(); 
	bool isBoardFull() const;
	char getFreeSpaceValue(int x, int y) const; //Returns the value of a certain item in the freeSpace array
	void setFreeSpaceValue(char value, int x, int y); //Sets the value of a certain item in the freeSpace array
	int getPlayerNum() const;
	void convertXYToFreeSpaceXY(int x, int y, int& freeSpaceX, int& freeSpaceY) const;

	int getHoleCount(); //To Board
	float getBumpinessLevel(int& maxHeight); //To Board
	int getFullLinesCount(); //To Board
private:
	void moveLinesDown(int line); //Moves all lines down by 1.

	int fillHeightsArr(int heights[]); //To Board
};
