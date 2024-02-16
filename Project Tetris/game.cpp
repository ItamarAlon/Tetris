#include "game.h"
#include "bot.h"

Game::Game(Board& board1, Board& board2, Bot& shape1, Bot& shape2, int _speed) : boardP1(board1), boardP2(board2), shapeP1(shape1), shapeP2(shape2), speed(_speed)
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
		cout << "("<< (int)GameConfig::menu::HUMANvHUMAN <<") Start a new Game" << endl;
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
	char key;
	ShowConsoleCursor(false); //During gameplay, we the cursor is turned off to make the game look better

	clrscr();
	boardP1.print();
	boardP2.print();

	while (!goToMenu) //The game keeps running, until a break happens (we'll see later)
	{
		//goToMenu = handleInput(); //At every frame of the game, the program checks if an input was given (and acts accordingly) using a function. If an input was made to pause the game, the function returns true
		//if (goToMenu)
		//	break; //In case the player decided to go to the menu, the program exist the while loop

		runGameForPlayer(boardP1, shapeP1); //The program runs the game for each player using a function
		//runGameForPlayer(boardP2, shapeP2); 

		for (int i = 0; i < 20; i++)
		{
			Sleep(speed/20); //Sleep is used in every run of the loop to slow the game down
			goToMenu = handleInput(); //At every frame of the game, the program checks if an input was given (and acts accordingly) using a function. If an input was made to pause the game, the function returns true
			if (goToMenu)
				break; //In case the player decided to go to the menu, the program exist the while loop
		}

		if (boardP1.isBoardFull() || boardP2.isBoardFull()) 
			break; //If one of the blocks is full, we exit the loop (because the game ends)
	}

	if (!goToMenu) //After exiting the loop, we check if the player wanted to go to the menu. If he didn't, it means the game ended so the winner is declared. Otherwise, the program exits the function (right back to the menu function)
		handleWinner();
}

void Game::runGameForPlayer(Board& board, Shape& shape)
{
	//In every frame:
	bool IsShapeInAir = shape.moveShapeDown(); //The program moves the shape down the board, and updates whether or not the shape is still on the ground.
	board.updateIsFull(); //Function that updates whether the board of the player is full or not

	if (!IsShapeInAir)
	{
		if (board.checkFullLine()) //If the shape landed, the program checks if there are any full lines that were deleted.
			board.print(); //If there were, it prints the board again (which was updated)
		shape.setShape(); //Then a new Tetromino is set
	}
}

bool Game::handleInput()
{
	if (_kbhit())
	{
		char key = _getch(); //If a key was pressed, we save it

		switch (key)
		{
		case (char)GameConfig::Lkeys::LEFT:
		case (char)GameConfig::Lkeys::RIGHT:
			shapeP1.moveShapeLeftRight(key); //Using a function in case a shape needs to move Left/Right
			break;
		case (char)GameConfig::Lkeys::LEFT - 32:
		case (char)GameConfig::Lkeys::RIGHT - 32:
			shapeP1.moveShapeLeftRight(key + 32); //In case the uppercase version of the key was received..
			break;
		case (char)GameConfig::Lkeys::DOWN:
		case (char)GameConfig::Lkeys::DOWN - 32:
			shapeP1.moveShapeDown(); //If DOWN was pressed, we need to increase the shape's speed. So we move it down by 1 to mimik the feeling of increased speed
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
			isGamePaused = true; //If ESC was pressed, the game is paused...
			return true; //...and true is retured to move out of the endless loop in runGame(), and into the menu function
		default:
			break;
		}
	}
	return false; //Otherwise, false is returned so that the loop will continue.
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
	if ((input != (int)GameConfig::menu::HUMANvHUMAN && input != (int)GameConfig::menu::PAUSED_GAME && input != (int)GameConfig::menu::INSTRUCTIONS && input != (int)GameConfig::menu::EXIT) || (input == (int)GameConfig::menu::PAUSED_GAME && !isGamePaused))
	{
		clrscr();
		cout << "Invalid input. Try again"; //If the input is not valid, an appropriate message is printed, before the menu is printed again
		Sleep(1130);
	}
	else
		switch (input) //If the input is valid:
		{
		case (int)GameConfig::menu::HUMANvHUMAN:
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
			cout << "Thanks for Playing!" << endl; //If 9 was pressed, we print a small goodbye message
		}

	if (input == (int)GameConfig::menu::EXIT)
		return false; //false is returned to indicate the program need to print the menu again
	return true;
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
