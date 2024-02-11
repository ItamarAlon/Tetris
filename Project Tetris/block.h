#pragma once
#include "general.h"
#include "board.h"

class Board;

//This class handles the blocks of the tetrominoes, that's gonna appear on screen throught the game
class Block
{
	char ch; //Char that represents how the block is gonna appear on screen
    int x, y; //The block's coordinates on screen
public:
	Block(char _ch = ' ', int _x = 0, int _y = 0);
	void moveTo(int x, int y); //This function moves the block to given coordinates
	void moveBy(int x, int y); //This function moves the block by x and y values (compared to it's current location on-screen)
	void print();
	void setX(int x);
	void setY(int y);
	int getX() const;
	int getY() const;
	void setCords(int x, int y);
	void setChar(char ch);
	char getChar();
	void moveBlockLeftRight(char key); //This function moves the block 1 place to the left/right (depending on the input from the keyboard)
	bool isSpaceTakenOffset(int offsetX, int offsetY, Board& playerBoard); //This function checks if the space on board, relative to the block's location, is free or not.
	void getOffsetFromInput(char key, int& offsetX, int& offsetY); // This function returns the 2 offset value (relative to the block's location), according to the input taken from the keyboard.
	void getFreeSpaceXY(Board& playerBoard, int& x, int& y); //This function returns the coordinates of the block in the freeSpace array (from the board class).
};

