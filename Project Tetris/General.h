#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <process.h>
#include <cmath>
using namespace std;

void gotoxy(int, int); //Function that moves the cursor to specific coordinates on-screen
void clrscr(); //Clears the entire screen.
void ShowConsoleCursor(bool showFlag); //Function that deleted/returns the cursor when needed. Used so that there won't be a cursor on-screen during gameplay.
char getCapital(char ch); //Returns the uppercase version of a letter (if it doesn't receive a letter from the ABC, it returns the char itself)
char getLowerCase(char capital); //Returns the lowercase version of a letter (if it doesn't receive a letter from the ABC, it returns the char itself)
float calcAverage(int arr[], int size); //Calculates the average of an int array
float standardDeviation(int arr[], int size); //Calculates the standard deviation of an int array
bool oneInXChance(int x); //has a 1 in X chance to return true. Otherwise, returns false.
int generateNumberInInterval(int a, int b); //Generates a random number between a and b (including)

