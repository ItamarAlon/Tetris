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
char getLowerCase(char capital);
float calcAverage(int arr[], int size);
float standardDeviation(int arr[], int size);
bool oneInXChance(int x);
//template<class Type>void swap(Type& a, Type& b);
int generateNumberInInterval(int a, int b);

//template<class Type>
//inline void swap(Type& a, Type& b)
//{
//	Type tmp = a;
//	a = b;
//	b = tmp;
//}
