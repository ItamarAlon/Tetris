#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <process.h>
#include "General.h"

//All the game configurations
class GameConfig
{
public:
	enum class Lkeys { LEFT = 'a', RIGHT = 'd', CLOCKWISE = 's', COUNTER_CLOCKWISE = 'w', ESC = 27, DOWN = 'x'};
	enum class Rkeys { LEFT = 'j', RIGHT = 'l', CLOCKWISE = 'k', COUNTER_CLOCKWISE = 'i', DOWN = 'm' }; // enum classes of the game's controls
	static constexpr int BOARD_WIDTH = 12;
	static constexpr int BOARD_HEIGHT = 18;  //The Width and Height of the boards in the game
};

