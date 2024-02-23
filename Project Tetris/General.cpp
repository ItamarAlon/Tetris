#include "general.h"


void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void clrscr()
{
	system("cls");
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; 
	SetConsoleCursorInfo(out, &cursorInfo);
}

char getCapital(char ch)
{
	if (ch >= 'a' && ch <= 'z')
		return ch - 32;
	return ch;
}

char getLowerCase(char capital)
{
	if (capital >= 'A' && capital <= 'Z')
		return capital + 32;
	return capital;
}

float calcAverage(int arr[], int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
		sum += arr[i];

	return (float)sum / (float)size;
}

float standardDeviation(int arr[], int size)
{
	float average = calcAverage(arr, size);
	float variance = 0;

	for (int i = 0; i < size; i++)
		variance += pow(arr[i] - average, 2);
	variance /= size;

	return sqrt(variance);
}

bool oneInXChance(int x)
{
	int random = rand() % x;
	if (random == 0)
		return true;
	return false;
}
