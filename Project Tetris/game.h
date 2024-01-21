#pragma once
#include "Libraries.h"

#include "shape.h"
#include "Board.h"

//class Block;
class Shape;
class Board;

class Game
{
	Board &boardP1, &boardP2;
	Shape &shapeP1, &shapeP2;
	int speed; 
	bool isGamePaused = false;

public:
	Game(Board& board1, Board& board2, Shape& shape1, Shape& shape2, int _speed = 200);
	int printMenu();
	void printInstructions();
	void runGame();
	int handleInput();
	void restartGame();
	void handleMenuInput(char input);
};

