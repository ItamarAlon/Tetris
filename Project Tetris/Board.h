#pragma once
#include "Libraries.h"
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
	bool isLineDeleted = false; //Tells if a line was deleted on-screen or not

	Board(int x, int y, int _playerNum);
	void resetBoard(); //Function that returns the board to it's default form at the start of the game.
	bool isSpaceTaken(int freeSpaceX, int freeSpaceY); //Checks if certain cords (in the freeSpace array) are taken.
	void print();
	int getXStart();
	int getYStart();
	int getWidth();
	int getHeight();
	void checkFullLine(); //Checks if there is a line full of blocks on the board, and deletes it if there is one, while moving all lines above it down.
	void moveLinesDown(int line); //Moves all lines down by 1.
	void updateIsFull(); 
	bool isBoardFull();
	char getFreeSpaceValue(int x, int y); //Returns the value of a certain item in the freeSpace array
	void setFreeSpaceValue(char value, int x, int y); //Sets the value of a certain item in the freeSpace array
	int getPlayerNum();
};
