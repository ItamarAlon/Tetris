#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "general.h"
#include "gameConfig.h"
#include "shape.h"
#include "board.h"
using namespace std;

#define TIE -1
class Player;
class Bot;
class Human;
class Shape;
class Board;
class Bomb;

//Class that handles all the activities that happen during the game, including the menu, the shapes' movement, etc..
class Game
{
	Player *player1, *player2;

	//Board &boardP1, &boardP2; //The 2 boards used during the game (1 for each player)
	//Shape &shapeP1, &shapeP2; //The shapes that are gonna appear in each board
	bool isGamePaused = false; //Tells if the game is in paused mode or not (used for the menu)

public:
	Game(Board& board1, Board& board2);
	~Game();
	void openMenu();
	void printInstructions();
	int chooseBotLevel(int botPlayerNum, bool onlyPlayer);
	void runGame(); //Function that runs the game itself, including moving the shapes down, checking for any input from the player, etc..
	void restartGame(); //Restarts the game that's currently running, in order to start a new game if needed.
	bool setPlayers(int input); //Sets up the players for the game

private:
	void runGameForPlayer(Player* player); //Function that runs the game for a specific player (used in runGame() to handle both players)
	bool handleGameInput(); //Handles all the input from the keyboard
	bool handleMenuInput(int input); //Handles all the input in the menu.
	bool isMenuInputValid(int input);
	void handleWinner(); //Checks who's the winning player at the end of the game, and prints a congratulation message.
	bool handleBotMenuInput(int input);
};

