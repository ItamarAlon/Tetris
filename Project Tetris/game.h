#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "general.h"
#include "gameConfig.h"
#include "shape.h"
#include "board.h"
//#include "human.h"
using namespace std;

#define TIE -1
class Bot;
class Human;
class Shape;
class Board;

//Class that handles all the activities that happen during the game, including the menu, the shapes' movement, etc..
class Game
{
	Board &boardP1, &boardP2; //The 2 boards used during the game (1 for each player)
	Human &shapeP1, &shapeP2; //The shapes that are gonna appear in each board.
	int speed; //The speed of the game
	bool isGamePaused = false; //Tells if the game is in paused mode or not (used for the menu)

public:
	Game(Board& board1, Board& board2, Human& shape1, Human& shape2, int _speed = 200);
	void openMenu();
	void printInstructions();
	void runGame(); //Function that runs the game itself, including moving the shapes down, checking for any input from the player, etc..
	void runGameForPlayer(Board& board, Human& shape); //Function that runs the game for a specific player (used in runGame() to handle both players)
	bool handleInput(); //Handles all the input from the keyboard
	void restartGame(); //Restarts the game that's currently running, in order to start a new game if needed.
	bool handleMenuInput(int input); //Handles all the input in the menu.
	void handleWinner(); //Checks who's the winning player at the end of the game, and prints a congratulation message.
};

