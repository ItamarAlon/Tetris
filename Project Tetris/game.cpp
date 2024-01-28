#include "game.h"

Game::Game(Board& board1, Board& board2, Shape& shape1, Shape& shape2, int _speed) : boardP1(board1), boardP2(board2), shapeP1(shape1), shapeP2(shape2), speed(_speed)
{
}

void Game::openMenu()
{
	int input;
	bool continueLoop = true;

	while (continueLoop)
	{
		ShowConsoleCursor(true); //In the menu the cursor should appear (as input is received from the player)
		clrscr();
		cout << "Welcome to Tetris! Pick one of the options below:\n\n";
		cout << "(1) Start a new Game" << endl;
		if (isGamePaused) 
			cout << "(2) Continue a paused game" << endl; //This option appears only if the game was paused by the players
		cout << "(8) Present instructions and keys" << endl;
		cout << "(9) EXIT" << endl;

		cin >> input;
		continueLoop = handleMenuInput(input); //A separate function is used to handle the input. The function also returns whether the menu should be printed again or not
	}
}

void Game::printInstructions()
{
	const char* boldStart = "\033[1m";
	const char* boldEnd = "\033[0m"; //To make the text bold

	clrscr();
	cout << "In Tetris, the primary objective is to manipulate falling geometric shapes, called tetrominoes, to\ncreate complete horizontal rows. The game continues until the stack of tetrominoes reaches the top of the screen.\n\n";

	cout << "How to Play:" << endl;
	cout << boldStart << "Shape Manipulation: " << boldEnd << "The players can move their shape Left/Right, rotate it, and accelerate it's descent.\nSee the Controls section for move info." << endl;
	cout << boldStart << "Clearing Rows: " << boldEnd << "When a horizontal line is filled with blocks, it disappears, and all the lines above it go down." << endl;
	cout << boldStart << "Game Over: " << boldEnd << "The game ends when for one of the players, the newly spawned tetromino cannot fit due to a lack of space at the top.\nThe player who achieves that first, loses the game. If both players lose at the same time, the game ends in a tie." << endl << endl;
	cout << boldStart << "Controls:" << boldEnd << endl;
	cout << "Move left: '"<< getCapital((char)GameConfig::Lkeys::LEFT) <<"' (for Left Player) Or '" << getCapital((char)GameConfig::Rkeys::LEFT) << "' (for Right Player)" << endl;
	cout << "Move right: '" << getCapital((char)GameConfig::Lkeys::RIGHT) << "' (for Left Player) Or '" << getCapital((char)GameConfig::Rkeys::RIGHT) << "' (for Right Player)" << endl;
	cout << "Rotate clockwise: '" << getCapital((char)GameConfig::Lkeys::CLOCKWISE) << "' (for Left Player) Or '" << getCapital((char)GameConfig::Rkeys::CLOCKWISE) << "' (for Right Player)" << endl;
	cout << "Rotate counterclockwise: '" << getCapital((char)GameConfig::Lkeys::COUNTER_CLOCKWISE) << "' (for Left Player) Or '" << getCapital((char)GameConfig::Rkeys::COUNTER_CLOCKWISE) << "' (for Right Player)" << endl;
	cout << "Accelerate shape: '" << getCapital((char)GameConfig::Lkeys::DOWN) << "' (for Left Player) Or '" << getCapital((char)GameConfig::Rkeys::DOWN) << "' (for Right Player)" << endl;
	cout << "*Both lowercase and uppercase letters should work" << endl;

	cout << "\n\nPress any key to return to main menu.";

	while (!_kbhit()){} //The program waits until a key is pressed, before exiting the function
}

void Game::runGame()
{
	bool goToMenu = false;
	ShowConsoleCursor(false);

	clrscr();
	boardP1.print();
	boardP2.print();

	while (true)
	{
		goToMenu = handleInput();
		if (goToMenu)
			break;

		shapeP1.IsShapeInAir = shapeP1.moveShapeDown();
		shapeP2.IsShapeInAir = shapeP2.moveShapeDown();
		Sleep(speed);

		boardP1.updateIsFull();
		boardP2.updateIsFull();

		if (boardP1.isBoardFull() || boardP2.isBoardFull())
			break;

		if (shapeP1.IsShapeInAir == false)
		{
			shapeP1.setShape();
			boardP1.checkFullLine();
			if (boardP1.isLineDeleted)
			{
				boardP1.print();
				boardP1.isLineDeleted = false;
			}
		}

		if (shapeP2.IsShapeInAir == false)
		{
			shapeP2.setShape();
			boardP2.checkFullLine();
			if (boardP2.isLineDeleted)
			{
				boardP2.print();
				boardP2.isLineDeleted = false;
			}
		}
		goToMenu = handleInput();
		if (goToMenu)
			break;
		
	}

	if (!goToMenu)
		handleWinner();
}

bool Game::handleInput()
{
	if (_kbhit())
	{
		char key = _getch();

		switch (key)
		{
		case (char)GameConfig::Lkeys::LEFT:
		case (char)GameConfig::Lkeys::RIGHT:
			shapeP1.moveShapeLeftRight(key);
			break;
		case (char)GameConfig::Lkeys::LEFT - 32:
		case (char)GameConfig::Lkeys::RIGHT - 32:
			shapeP1.moveShapeLeftRight(key + 32);
			break;
		case (char)GameConfig::Lkeys::DOWN:
		case (char)GameConfig::Lkeys::DOWN - 32:
			shapeP1.moveShapeDown();
			break;
		case (char)GameConfig::Lkeys::CLOCKWISE:
		case (char)GameConfig::Lkeys::COUNTER_CLOCKWISE:
			shapeP1.rotateShape(key);
			break;
		case (char)GameConfig::Lkeys::CLOCKWISE - 32:
		case (char)GameConfig::Lkeys::COUNTER_CLOCKWISE - 32:
			shapeP1.rotateShape(key + 32);
			break;



		case (char)GameConfig::Rkeys::LEFT:
		case (char)GameConfig::Rkeys::RIGHT:
			shapeP2.moveShapeLeftRight(key);
			break;
		case (char)GameConfig::Rkeys::LEFT - 32:
		case (char)GameConfig::Rkeys::RIGHT - 32:
			shapeP2.moveShapeLeftRight(key + 32);
			break;
		case (char)GameConfig::Rkeys::DOWN:
		case (char)GameConfig::Rkeys::DOWN - 32:
			shapeP2.moveShapeDown();
			break;
		case (char)GameConfig::Rkeys::CLOCKWISE:
		case (char)GameConfig::Rkeys::COUNTER_CLOCKWISE:
			shapeP2.rotateShape(key);
			break;
		case (char)GameConfig::Rkeys::CLOCKWISE - 32:
		case (char)GameConfig::Rkeys::COUNTER_CLOCKWISE - 32:
			shapeP2.rotateShape(key + 32);
			break;


		case (char)GameConfig::Lkeys::ESC:
			isGamePaused = true;
			return true;
		default:
			break;
		}
	}
	return false;
}

void Game::restartGame()
{
	boardP1.resetBoard();
	boardP2.resetBoard();

	shapeP1.setShape();
	shapeP2.setShape();
}

bool Game::handleMenuInput(int input)
{
	if ((input != 1 && input != 2 && input != 8 && input != 9) || (input == 2 && !isGamePaused)) //If the input is not valid, an appropriate message is printed, before the menu is printed again
	{
		clrscr();
		cout << "Invalid input. Try again";
		Sleep(1130);
	}
	else
		switch (input)
		{
		case 1:
			if (isGamePaused)
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

	if (input == 9)
		return false;
	return true;
}

void Game::handleWinner()
{
	int winner;
	if (boardP1.isBoardFull() && !boardP2.isBoardFull())
		winner = boardP2.getPlayerNum();
	else if (!boardP1.isBoardFull() && boardP2.isBoardFull())
		winner = boardP1.getPlayerNum();
	else
		winner = TIE;

	clrscr();
	if (winner == TIE)
		cout << "The game ended in a tie. Wow!" << endl;
	else
		cout << "Player #" << winner << " is the winner! Congratulations player #" << winner << "!" << endl;
	cout << "Good Game everyone! Hope to see you all in another game!" << endl << endl;
	cout << "Press any key to return to the main menu";

	Sleep(800);
	ShowConsoleCursor(true);
	while (!_kbhit()) {}
	isGamePaused = false;
	restartGame();
}
