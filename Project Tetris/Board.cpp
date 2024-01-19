#include "Board.h"

//void Board::resetBoard() {
//	int i, j;
//	for (i = 1; i < 11; i++) {
//		for (j = 1; j < 21; j++) {
//			this->freeSpace[i][j] = true;
//
//		}
//	}
//}
Board::Board(int x, int y, int _playerNum) :X_START(x), Y_START(y), playerNum(_playerNum)
{
	//for (int i = 0; i < WIDTH + 1; i++)
	//{
	//	this->freeSpace[i][0] = 186; 
	//	this->freeSpace[i][HEIGHT + 1] = 186; 
	//}
	//for (int i = 0; i < HEIGHT + 2; i++)
	//{
	//	freeSpace[0][i] = 220; 
	//	freeSpace[WIDTH][i] = 223; 
	//}
	//for (int i = 1; i < WIDTH; i++)
	//{
	//	for (int j = 1; j < HEIGHT + 1; j++)
	//	{
	//		this->freeSpace[i][j] = ' ';
	//	}
	//}


	for (int i = 1; i < WIDTH; i++) {
		for (int j = 1; j < HEIGHT + 1; j++) {
			this->freeSpace[i][j] = true;

		}
	}
}

void Board::print()
{
	for (int col = this->X_START; col <= this->X_END; col++) //print ceiling and floor
	{
		gotoxy(col, this->Y_START);
		cout << (char)220;

		gotoxy(col, this->Y_END + 1);
		cout << (char)223;
	}

	for (int row = this->Y_START + 1; row <= this->Y_END; row++) //print walls
	{
		gotoxy(this->X_START, row);
		cout << (char)186;

		gotoxy(this->X_END, row);
		cout << (char)186;
	}
}

bool Board::checkFreeSpaceCoordinates(int freeSpaceX, int freeSpaceY)
{
	if (freeSpace[freeSpaceX][freeSpaceY] == false)
		return true;
	return false;
}

void Board::printFreeSpace()
{
	gotoxy(0, 0);
	for (int i = 0; i < WIDTH + 1; i++)
	{
		for (int j = 0; j < HEIGHT + 2; j++)
		{
			if (freeSpace[i][j] == true)
				cout << "O";
			else
				cout << "X";
		}
		cout << endl;
	}
}

//void Board::moveBlockDownBoard(Block block, int speed)
//{
//	//block.setCords(X_START + WIDTH / 2, Y_START + 1);
//	char key;
//
//	for (int i = 0; i < HEIGHT - 1; i++)
//	{
//		Game::moveBlockLeftRight(block, playerNum);
//		block.print();
//		Sleep(speed);
//		block.moveBy(0, 1);
//		block.print();
//	}
//}

