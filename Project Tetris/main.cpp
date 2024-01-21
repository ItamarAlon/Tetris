#include "shape.h"
#include "game.h"
#include "Block.h"
#include "Board.h"

#include "Libraries.h"

void main()
{
	srand(time(nullptr));
	Board board;
	Shape s(board);
	Game game(board, s);


	//game.runGame();

	
	game.printMenu();
	//switch (menuInput)
	//{
	//case 1:
	//	game.runGame();
	//case 8:
	//	game.printInstructions(); //Will code this function later
	//	break;
	//}
}