#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <process.h>
#include "general.h"

//All the game configurations
class GameConfig
{
public:
	enum class Lkeys { LEFT = 'a', RIGHT = 'd', CLOCKWISE = 's', COUNTER_CLOCKWISE = 'w', ESC = 27, DOWN = 'x'};
	enum class Rkeys { LEFT = 'j', RIGHT = 'l', CLOCKWISE = 'k', COUNTER_CLOCKWISE = 'i', DOWN = 'm' }; // enum classes of the game's controls
	enum class menu { HUMANvHUMAN = 1, HUMANvCOMPUTER = 2, COMPUTERvCOMPUTER = 3, PAUSED_GAME = 4, INSTRUCTIONS = 8, EXIT = 9 };
	static constexpr int BOARD_WIDTH = 12;
	static constexpr int BOARD_HEIGHT = 18;  //The Width and Height of the boards in the game
};

