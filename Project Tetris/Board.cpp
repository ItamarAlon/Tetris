#include "board.h"

Board::Board(int x, int y) : X_START(x), Y_START(y)
{
	resetBoard();
}

Board::Board(const Board& oldBoard) : X_START(oldBoard.X_START), Y_START(oldBoard.Y_START)
{
	*this = oldBoard;
}

Board& Board::operator=(const Board& oldBoard)
{
	if (&oldBoard != this)
		for (int row = 0; row < HEIGHT + 1; row++)
			for (int col = 0; col < WIDTH + 2; col++)
				freeSpace[row][col] = oldBoard.freeSpace[row][col];
	return *this;
}

void Board::resetBoard() 
{
	for (int row = 1; row < HEIGHT + 1; row++)
	{
		freeSpace[row][0] = 186;
		freeSpace[row][WIDTH + 1] = 186; //For the walls of the border, a special char is set (186 in ascii)
		for (int col = 1; col < WIDTH + 1; col++)
			this->freeSpace[row][col] = ' '; //And for the rest of the row, ' ' is set (to represent an empty space)
	}
	for (int col = 0; col < WIDTH + 2; col++) //For the roof and ceiling of the border, special chars are set (220 and 223)
	{
		this->freeSpace[0][col] = 220;
		this->freeSpace[HEIGHT + 1][col] = 223;
	}
	isFull = false;
}

bool Board::isSpaceTaken(int freeSpaceX, int freeSpaceY) const
{
	if (freeSpace[freeSpaceY][freeSpaceX] != ' ') 
		return true; //if the value of freeSpace is ' ', then the space on board is taken. So true is returned
	return false;
}

bool Board::clearFullLines()
{
	bool lineDeleted = false;
	for (int row = HEIGHT; row > 0; row--) //The loop starts from the end of the board, where it's most likely that a line will be full of blocks.
	{
		if (isLineFull(row)) 
		{
			lineDeleted = true;
			moveLinesDown(row); //If a line is full, another function is called to moves all the lines above it 1 place down.
			row++;
		}
	}
	return lineDeleted;
}

bool Board::isLineFull(int row)
{
	if (row < 1 || row > HEIGHT) //Just in the an illegal row number was given
		row = HEIGHT;

	for (int col = 1; col < WIDTH + 1; col++)
		if (freeSpace[row][col] == ' ')
			return false; //If there's a space in the line not taken, then the line if not full. So the for loop stops (as there's no need to check anymore)
	return true;
}

void Board::moveLinesDown(int line)
{
	for (int row = line; row > 1; row--)
		for (int col = 0; col < WIDTH + 1; col++)
			freeSpace[row][col] = freeSpace[row - 1][col]; //Every space in the freeSpace array is overwritten by the value "above" it
}

int Board::getHoleCount()
{
	int holeCounter = 0, row;

	for (int col = 1; col <= WIDTH; col++)
	{
		row = 1;
		while (!isSpaceTaken(col, row))
			row++; //Everytime a space is not taken, we move 1 space down

		while (row < HEIGHT) //When we reach a taken space, if it's not the floor, we keep moving down the lines
		{
			row++;
			if (!isSpaceTaken(col, row)) //Now, whenever we get a free space, it's a space under a block. So we consider it a hole and use the counter accordingly
				holeCounter++;
		}
	}

	return holeCounter;
}

float Board::getBumpinessLevel(int& maxHeight)
{
	int heights[GameConfig::BOARD_WIDTH] = {};
	maxHeight = fillHeightsArr(heights);
	//The bumpiness level of a board is determined by the standard deviation of all the column heights on the board. So if the difference in heights is bigger, the bumpiness level is higher
	return standardDeviation(heights, WIDTH); 
}

int Board::getFullLinesCount()
{
	int fullLineCounter = 0;

	for (int row = HEIGHT; row > 0; row--)
		if (isLineFull(row))
			fullLineCounter++;

	return fullLineCounter;
}

int Board::fillHeightsArr(int heights[])
{
	int maxHeight = heights[0] = getColumnHeight(1);

	for (int i = 1; i < GameConfig::BOARD_WIDTH; i++)
	{
		heights[i] = getColumnHeight(i + 1);
		if (heights[i] > maxHeight)
			maxHeight = heights[i];
	}
	return maxHeight;
}

void Board::updateIsFull()
{
	isFull = isSpaceTaken(WIDTH / 2, 2); //The board is full if the space where the tetrominoes are supposed to spawn from, is taken.
}

bool Board::isBoardFull() const
{
	return isFull;
}

char Board::getFreeSpaceValue(int x, int y) const
{
	return freeSpace[y][x];
}

void Board::setFreeSpaceValue(char value, int x, int y)
{
	freeSpace[y][x] = value;
}

void Board::print() const
{
	for (int row = 0; row < HEIGHT + 2; row++)
	{
		gotoxy(X_START, Y_START + row); //The cursor moves to the coordinates where the board is supposed to start in (which are X_START and Y_START), but "row" spaces down 
		for (int col = 0; col < WIDTH + 2; col++)
			cout << freeSpace[row][col];
	}
}

int Board::getXStart() const
{
	return X_START;
}

int Board::getYStart() const
{
	return Y_START;
}

int Board::getWidth() const
{
	return WIDTH;
}

int Board::getHeight() const
{
	return HEIGHT;
}

int Board::getColumnHeight(int col) const
{
	if (col < 1 || col > WIDTH)
		return -1;

	int row = 1;
	while (freeSpace[row][col] == ' ')
		row++;

	return HEIGHT - row + 1;
}

void Board::convertXYToFreeSpaceXY(int x, int y, int& freeSpaceX, int& freeSpaceY) const
{
	freeSpaceX = x - X_START; //The cords of a block in the freeSpace array is calculated by taking the cords of the block on-screen, and removing the Boards' cords on-screen.
	freeSpaceY = y - Y_START;
}


