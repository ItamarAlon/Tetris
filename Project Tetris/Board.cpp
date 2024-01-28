#include "Board.h"

Board::Board(int x, int y, int _playerNum) :X_START(x), Y_START(y), playerNum(_playerNum)
{
	resetBoard();
}

void Board::resetBoard() 
{
	for (int i = 1; i < HEIGHT + 1; i++)
	{
		freeSpace[i][0] = 186;
		freeSpace[i][WIDTH + 1] = 186;
		for (int j = 1; j < WIDTH + 1; j++)
		{
			this->freeSpace[i][j] = ' ';
		}
	}
	for (int i = 0; i < WIDTH + 2; i++)
	{
		this->freeSpace[0][i] = 220;
		this->freeSpace[HEIGHT + 1][i] = 223;
	}
}

//Board& Board::operator=(const Board& newBoard)
//{
//	this->X_START = newBoard.X_START;
//	this->Y_START = newBoard.Y_START;
//	this->playerNum = newBoard.playerNum;
//	return *this;
//}

//void Board::print()
//{
//	for (int col = this->X_START; col <= this->X_END; col++) //print ceiling and floor
//	{
//		gotoxy(col, this->Y_START);
//		cout << (char)220;
//
//		gotoxy(col, this->Y_END + 1);
//		cout << (char)223;
//	}
//
//	for (int row = this->Y_START + 1; row <= this->Y_END; row++) //print walls
//	{
//		gotoxy(this->X_START, row);
//		cout << (char)186;
//
//		gotoxy(this->X_END, row);
//		cout << (char)186;
//	}
//} 

bool Board::isSpaceTaken(int freeSpaceX, int freeSpaceY)
{
	if (freeSpace[freeSpaceY][freeSpaceX] != ' ')
		return true;
	return false;
}

void Board::checkFullLine()
{
	bool fullLine, lineDeleted = false;
	for (int i = HEIGHT; i > 0; i--)
	{
		fullLine = true;
		for (int j = 1; j < WIDTH + 1; j++)
		{
			if (freeSpace[i][j] == ' ')
			{
				fullLine = false;
				break;
			}

		}
		if (fullLine)
		{
			lineDeleted = true;
			moveLinesDown(i);
			i++;

		}
	}
	this->isLineDeleted = lineDeleted;
}

void Board::moveLinesDown(int line)
{
	for (int i = line; i > 1;i--) 
	{
		for (int j = 0; j < WIDTH+1; j++)
		{
			freeSpace[i][j] = freeSpace[i - 1][j];
		} 
	
	}
}

void Board::updateIsFull()
{
	isFull = isSpaceTaken(WIDTH / 2, 1);
}

bool Board::isBoardFull()
{
	return isFull;
}

char Board::getFreeSpaceItem(int x, int y)
{
	return freeSpace[y][x];
}

void Board::setFreeSpaceItem(char value, int x, int y)
{
	freeSpace[y][x] = value;
}

int Board::getPlayerNum()
{
	return playerNum;
}

void Board::print()
{
	//gotoxy(x, y);
	for (int i = 0; i < HEIGHT + 2; i++)
	{
		gotoxy(X_START, Y_START + i);
		for (int j = 0; j < WIDTH + 2; j++)
		{
			cout << freeSpace[i][j];
			//if (freeSpace[j][i] == true)
			//	cout << "O";
			//else
			//	cout << "X";
		}
		//cout << endl;
	}
}

int Board::getXStart()
{
	return X_START;
}

int Board::getYStart()
{
	return Y_START;
}

int Board::getWidth()
{
	return WIDTH;
}

int Board::getHeight()
{
	return HEIGHT;
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

