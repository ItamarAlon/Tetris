#include "game.h"
#include "human.h"
#include "bot.h"

Game::Game(Board& board1, Board& board2, int _speed) : boardP1(board1), boardP2(board2), speed(_speed)
{
}

Game::~Game()
{
	delete shapeP1;
	delete shapeP2;
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
		cout << "("<< (int)GameConfig::menu::HUMANvHUMAN <<") Start a new Game - Human vs Human" << endl;
		cout << "(" << (int)GameConfig::menu::HUMANvCOMPUTER << ") Start a new Game - Human vs Computer" << endl;
		cout << "(" << (int)GameConfig::menu::COMPUTERvCOMPUTER << ") Start a new Game - Computer vs Computer" << endl;
		if (isGamePaused) 
			cout << "(" << (int)GameConfig::menu::PAUSED_GAME << ") Continue a paused game" << endl; //This option appears only if the game was paused by the players
		cout << "(" << (int)GameConfig::menu::INSTRUCTIONS << ") Present instructions and keys" << endl;
		cout << "(" << (int)GameConfig::menu::EXIT << ") EXIT" << endl;

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

	_getch(); //The program waits until a key is pressed, before exiting the function
}

void Game::runGame()
{
	bool goToMenu = false;
	ShowConsoleCursor(false); //During gameplay, we the cursor is turned off to make the game look better

	clrscr();
	boardP1.print();
	boardP2.print();

	while (!goToMenu) //The game keeps running, until a break happens (we'll see later)
	{
		runGameForPlayer(boardP1, shapeP1); //The program runs the game for each player using a function
		runGameForPlayer(boardP2, shapeP2);

		for (int i = 0; i < 10; i++)
		{
			Sleep(speed / 10); //Sleep is used in every run of the loop to slow the game down
			goToMenu = handleInput(); //At every frame of the game, the program checks if the ESC key was pressed. If it did, the function returns true, and the program exits the loop
			if (goToMenu)
				break; //In case the player decided to go to the menu, the program exits the while loop
		}

		if (boardP1.isBoardFull() || boardP2.isBoardFull())
			break; //If one of the blocks is full, we exit the loop (because the game ends)
	}

	if (!goToMenu) //After exiting the loop, we check if the player wanted to go to the menu. If he didn't, it means the game ended so the winner is declared. Otherwise, the program exits the function (right back to the menu function)
		handleWinner();
}

void Game::runGameForPlayer(Board& board, Shape* shape)
{
	//In every frame:
	bool IsShapeInAir = shape->moveShapeDown(); //The program moves the shape down the board, and updates whether or not the shape is still on the ground.
	board.updateIsFull(); //Function that updates whether the board of the player is full or not

	if (!IsShapeInAir)
	{
		if (board.checkFullLine()) //If the shape landed, the program checks if there are any full lines that were deleted.
			board.print(); //If there were, it prints the board again (which was updated)
		shape->setShape(); //Then a new Tetromino is set
	}
}

bool Game::handleInput()
{
	char input = ' ';
	if (_kbhit())
		input = _getch(); //If a key was pressed, we save it

	if (input == (char)GameConfig::Lkeys::ESC)
	{
		isGamePaused = true; //If ESC was pressed, the game is paused...
		return true;
	}

	shapeP1->takeAction(input);
	shapeP2->takeAction(input);
	return false; //False is returned so that the loop will continue.
}

void Game::restartGame()
{
	boardP1.resetBoard();
	boardP2.resetBoard();

	shapeP1->setShape();
	shapeP2->setShape();
}

bool Game::handleMenuInput(int input)
{
	if (isMenuInputValid(input))
	{
		switch (input)
		{
		case (int)GameConfig::menu::HUMANvHUMAN:
			shapeP1 = new Human(boardP1);
			shapeP2 = new Human(boardP2);
			break;
		case (int)GameConfig::menu::HUMANvCOMPUTER:
			shapeP1 = new Human(boardP1);
			shapeP2 = new Bot(boardP2);
			break;
		case (int)GameConfig::menu::COMPUTERvCOMPUTER:
			shapeP1 = new Bot(boardP1);
			shapeP2 = new Bot(boardP2);
			break;
		default:
			break;
		}
		switch (input)
		{
		case (int)GameConfig::menu::HUMANvHUMAN:
		case (int)GameConfig::menu::HUMANvCOMPUTER:
		case (int)GameConfig::menu::COMPUTERvCOMPUTER:
			if (isGamePaused)
				restartGame(); //If 1 was pressed, we restart the game before running it again (only if the game is paused, otherwise there's no need to restart)
			runGame();
			break;
		case (int)GameConfig::menu::PAUSED_GAME:
			runGame(); //If 2 was pressed, we run the game again. The boards and shapes haven't changed, so the game will continue right where it left off
			break;
		case (int)GameConfig::menu::INSTRUCTIONS:
			printInstructions();
			break;
		case (int)GameConfig::menu::EXIT:
			clrscr();
			cout << "Thanks for Playing!" << endl; //If EXIT was chosen, we print a small goodbye message...
			return false; //...and return false to indicate the program needs to exit the "menu" function and exit the game
		}
	}
	else
	{
		clrscr();
		cout << "Invalid input. Try again"; //If the input is not valid, an appropriate message is printed, before the menu is printed again
		Sleep(1130);
	}
	return true;
}

bool Game::isMenuInputValid(int input)
{
	if (input == (int)GameConfig::menu::PAUSED_GAME && isGamePaused)
		return true;

	switch (input)
	{
	case (int)GameConfig::menu::HUMANvHUMAN:
	case (int)GameConfig::menu::HUMANvCOMPUTER:
	case (int)GameConfig::menu::COMPUTERvCOMPUTER:
	case (int)GameConfig::menu::INSTRUCTIONS:
	case (int)GameConfig::menu::EXIT:
		return true;
	}

	return false;
}

void Game::handleWinner()
{
	//The programs enter this function only if one of the boards are full.
	int winner;
	if (boardP1.isBoardFull() && !boardP2.isBoardFull())
		winner = boardP2.getPlayerNum(); 
	else if (!boardP1.isBoardFull() && boardP2.isBoardFull())
		winner = boardP1.getPlayerNum();
	else
		winner = TIE; //If both boards are full, the game ends in a tie

	clrscr();
	if (winner == TIE)
		cout << "The game ended in a tie. Wow!" << endl;
	else
		cout << "Player #" << winner << " is the winner! Congratulations player #" << winner << "!" << endl;
	cout << "Good Game everyone! Hope to see you all in another game!" << endl << endl;
	cout << "Press any key to return to the main menu";

	Sleep(2000); //Sleep is used so that the end screen won't end unexpectedly because of a previous input from the game
	ShowConsoleCursor(true);
	_getch();
	isGamePaused = false; //Now that the game ended, it is not paused anymore
	restartGame(); //We restart to before starting a new game
}
