#include "game.h"

Game::Game(Board& board1, Board& board2, Shape& shape1, Shape& shape2, int _speed) : boardP1(board1), boardP2(board2), shapeP1(shape1), shapeP2(shape2), speed(_speed)
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

	boardP1.print();
	boardP2.print();
	while (true)
	{
		input = handleInput();
		if (input == 9)
			break;
		shapeP1.IsShapeInAir = shapeP1.moveShapeDown();
		shapeP2.IsShapeInAir = shapeP2.moveShapeDown();
		Sleep(speed);

		boardP1.isFull();
		boardP2.isFull();

		if (boardP1.isBoardFull || boardP2.isBoardFull)
			break;
		//gotoxy(0, 0);
		//if (boardP2.isFull())
		//	cout << "taken";
		//else
		//	cout << "not taken";

		if (shapeP1.IsShapeInAir == false)
		{
			shapeP1.setShape();
			boardP1.isLineDeleted = boardP1.checkFullLine();
			if (boardP1.isLineDeleted)
			{
				boardP1.print();
				boardP1.isLineDeleted = false;
			}
		}

		if (shapeP2.IsShapeInAir == false)
		{
			shapeP2.setShape();
			boardP2.isLineDeleted = boardP2.checkFullLine();
			if (boardP2.isLineDeleted)
			{
				boardP2.print();
				boardP2.isLineDeleted = false;
			}
		}
		
	}


	if (input != 9)
	{
		decideWinner();
	}
}

int Game::handleInput()
{
	int menuInput = -394;
	if (_kbhit())
	{
		char key = _getch();

		switch (key)
		{
		case (char)GameConfig::Lkeys::LEFT:
		case (char)GameConfig::Lkeys::RIGHT:
			shapeP1.moveShapeLeftRight(key);
			break;
		case (char)GameConfig::Lkeys::DOWN:
			//shape.speedUpShape();
			shapeP1.moveShapeDown();
			break;
		case (char)GameConfig::Lkeys::CLOCKWISE:
		case (char)GameConfig::Lkeys::COUNTER_CLOCKWISE:
			shapeP1.rotateShape(key);
			break;

		case (char)GameConfig::Rkeys::LEFT:
		case (char)GameConfig::Rkeys::RIGHT:
			shapeP2.moveShapeLeftRight(key);
			break;
		case (char)GameConfig::Rkeys::DOWN:
			//shape.speedUpShape();
			shapeP2.moveShapeDown();
			break;
		case (char)GameConfig::Rkeys::CLOCKWISE:
		case (char)GameConfig::Rkeys::COUNTER_CLOCKWISE:
			shapeP2.rotateShape(key);
			break;

		case (char)GameConfig::Lkeys::ESC:
			isGamePaused = true;
			menuInput = printMenu();
			break;
		default:
			break;
		}
	}
	return menuInput;
}

void Game::restartGame()
{
	boardP1.resetBoard();
	boardP2.resetBoard();

	shapeP1.setShape();
	shapeP2.setShape();
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

void Game::decideWinner()
{
	int winner;
	if (boardP1.isBoardFull && !boardP2.isBoardFull)
		winner = boardP2.playerNum;
	else if (!boardP1.isBoardFull && boardP2.isBoardFull)
		winner = boardP1.playerNum;
	else
		winner = TIE;


	Sleep(200);
	clrscr();
	if (winner != TIE)
		cout << "Player #" << winner << " is the winner! Congratulations player #" << winner << "!" << endl;
	else
		cout << "The game ended in a tie. Wow!" << endl;
	cout << "Good Game everyone! Hope to see you all in another game!" << endl << endl;
	cout << "Press any key to return to the main menu";

	Sleep(200);
	while (!_kbhit()) {}
	isGamePaused = false;
	printMenu();
}
