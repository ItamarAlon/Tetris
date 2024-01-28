#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <process.h>
using namespace std;

void gotoxy(int, int); //Function that moves the cursor to specific coordinates on-screen
void clrscr(); //Clears the entire screen.
void ShowConsoleCursor(bool showFlag); //Function that deleted/returns the cursor when needed. Used so that there won't be a cursor on-screen during gameplay.
char getCapital(char ch); //Returns the uppercase version of a letter (if it doesn't receive a letter from the ABC, it returns the char itself)