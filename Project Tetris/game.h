#pragma once
#include "Libraries.h"

#include "shape.h"
#include "Board.h"

//class Block;
class Shape;
class Board;

class Game
{
	Board &board;
	bool shapeP1 = true;
	Shape &shape;
	bool isLineDeleted = false;
public:
	Game(Board& board1, Shape& shape1);
	static int printMenu(bool isGamePaused);
	void printInstructions();
	void runGame();
};

