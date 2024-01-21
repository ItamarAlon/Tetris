#pragma once
#include "Libraries.h"

#include "shape.h"
#include "Board.h"

//class Block;
class Shape;
class Board;

class Game
{
	Board &boardP1;
	Shape &shapeP1;
	int speed; 
	bool isGamePaused = false;

public:
	Game(Board& board1, Shape& shape1, int _speed = 200);
	int printMenu();
	void printInstructions();
	void runGame();
	int handleInput(int playerNum);
	void restartGame();
	void handleMenuInput(char input);
};

