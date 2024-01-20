#include "game.h"

Game::Game(Board& board1, Shape& shape1) : board(board1), shape(shape1)
{
	
}

int Game::printMenu(bool isGamePaused)
{
	clrscr();
	cout << "Welcome to Tetris! Pick one of the options below:\n\n";
	cout << "(1) Start a new Game" << endl;
	if (isGamePaused)
		cout << "(2) Continue a paused game" << endl;
	cout << "(8) Present instructions and keys" << endl;
	cout << "(9) EXIT" << endl;

	int input;
	cin >> input;

	if ((input != 1 && input != 8 && input != 9) || (input == 2 && !isGamePaused))
	{
		clrscr();
		cout << "Invalid input. Try again";
		Sleep(1600);
		return printMenu(isGamePaused);
	}

	clrscr();
	return input;
}

void Game::printInstructions()
{
}

void Game::runGame()
{
	Board board;
	bool shapeP1 = true;
	Shape s(board);
	bool isDeleted = false;


	//board.print();
	board.printFreeSpace();
	while (true)
	{
		shapeP1 = s.moveShapeDown();
		Sleep(200);
		if (shapeP1 == false)
		{
			//board.printFreeSpace(0, 0);
			s.setShape(254);
			isDeleted = board.checkFullLine();
			//board.print();
			if (isDeleted)
			{
				board.printFreeSpace();
				isDeleted = false;
			}
		}
	}
}