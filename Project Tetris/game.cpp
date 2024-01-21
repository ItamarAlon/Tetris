#include "game.h"

Game::Game(Board& board1, Shape& shape1, int _speed) : boardP1(board1), shape(shape1), speed(_speed)
{
	
}

int Game::printMenu()
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

	if ((input != 1 && input != 8 && input != 9 && input != 2) || (input == 2 && !isGamePaused))
	{
		clrscr();
		cout << "Invalid input. Try again";
		Sleep(1100);
		return printMenu();
	}

	clrscr();
	handleMenuInput(input);
	return input;
}

void Game::printInstructions()
{
	const char* boldStart = "\033[1m";
	const char* boldEnd = "\033[0m";

	clrscr();
	//cout << "In Tetris, you must arrange a sequence of small shapes, called\n Tetraminos, into complete lines. As each line is completed, it will\n disappear from the screen. Tetraminos fall from the top of the play field to the bottom.\n Each Tetramino is made up of four blocks, arranged into\n seven different patterns."

	//Objective:
	cout << "In Tetris, the primary objective is to manipulate falling geometric shapes, called tetrominoes, to\ncreate complete horizontal rows. The game continues until the stack of tetrominoes reaches the top of the screen.\n\n";

	cout << "How to Play:" << endl;
	cout << boldStart << "Shape Manipulation: " << boldEnd << "Use 'A' and 'D' keys to move the tetrominoes left or right. The 'X' key accelerates their descent.\n'S' and 'W' keys rotate the shapes clockwise or counterclockwise, respectively." << endl;
	cout << boldStart << "Clearing Rows: " << boldEnd << "When a horizontal line is filled with blocks, it disappears, and all the lines above it go down" << endl;
	cout << boldStart << "Game Over: " << boldEnd << "The game ends if the newly spawned tetromino cannot fit due to a lack of space at the top." << endl;

	cout << "\n\nPress any key to return to main menu.";

	while (!_kbhit()){}
	printMenu();
}

void Game::runGame()
{
	int input;

	boardP1.printFreeSpace();
	while (true)
	{
		input = handleInput(boardP1.playerNum);
		if (input == 9)
			break;
		IsShapeP1InAir = shape.moveShapeDown();
		Sleep(speed);
		if (IsShapeP1InAir == false)
		{
			shape.setShape();
			isLineDeleted = boardP1.checkFullLine();
			if (isLineDeleted)
			{
				boardP1.printFreeSpace();
				isLineDeleted = false;
			}
		}
	}
}

int Game::handleInput(int playerNum)
{
	int menuInput = -394;
	if (_kbhit())
	{
		char key = _getch();

		if (playerNum == 1)
			switch (key)
			{
			case (char)GameConfig::Lkeys::LEFT:
			case (char)GameConfig::Lkeys::RIGHT:
				shape.moveShapeLeftRight(key, playerNum);
				break;
			case (char)GameConfig::Lkeys::ESC:
				isGamePaused = true;
				menuInput = printMenu();
				break;
			case (char)GameConfig::Lkeys::DOWN:
				//shape.speedUpShape();
				shape.moveShapeDown();
				break;
			case (char)GameConfig::Lkeys::CLOCKWISE:
			case (char)GameConfig::Lkeys::COUNTER_CLOCKWISE:
				shape.rotateShape(key);
				break;
			}
		else if (playerNum == 2)
			switch (key)
			{
			case (char)GameConfig::Rkeys::LEFT:
			case (char)GameConfig::Rkeys::RIGHT:
				shape.moveShapeLeftRight(key, playerNum);
				break;
			case (char)GameConfig::Rkeys::ESC:
				isGamePaused = true;
				menuInput = printMenu();
				break;
			case (char)GameConfig::Rkeys::DOWN:
				//shape.speedUpShape();
				shape.moveShapeDown();
				break;
			case (char)GameConfig::Rkeys::CLOCKWISE:
			case (char)GameConfig::Rkeys::COUNTER_CLOCKWISE:
				shape.rotateShape(key);
				break;
			}

	}
	return menuInput;
}

void Game::restartGame()
{
	boardP1.resetBoard();
	shape.setShape();
}

void Game::handleMenuInput(char input)
{
	switch (input)
	{
	case 1:
		restartGame();
		runGame();
		break;
	case 2:
		runGame();
		break;
	case 8:
		printInstructions();
		break;
	case 9:
		clrscr();
		cout << "Thanks for Playing!" << endl;
	}
}
