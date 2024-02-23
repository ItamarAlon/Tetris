#pragma once
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
	void print() const;
	void setX(int x);
	void setY(int y);
	int getX() const;
	int getY() const;
	void setCords(int x, int y);
	void setChar(char ch);
	char getChar() const;
	bool isSpaceTakenOffset(int offsetX, int offsetY, const Board& playerBoard) const; //This function checks if the space on board, relative to the block's location, is free or not.
	void getFreeSpaceXY(const Board& playerBoard, int& x, int& y) const; //This function returns the coordinates of the block in the freeSpace array (from the board class).
};