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
	enum class Lkeys { LEFT = 'a', RIGHT = 'd', CLOCKWISE = 's', COUNTER_CLOCKWISE = 'w', DOWN = 'x'};
	enum class Rkeys { LEFT = 'j', RIGHT = 'l', CLOCKWISE = 'k', COUNTER_CLOCKWISE = 'i', DOWN = 'm' }; // enum classes of the game's controls
	enum class menu { HUMANvHUMAN = 1, HUMANvCOMPUTER = 2, COMPUTERvCOMPUTER = 3, PAUSED_GAME = 4, INSTRUCTIONS = 8, EXIT = 9 }; //for the menu
	enum class Type { HUMAN = true, BOT = false };
	enum class Direction { LEFT, RIGHT };
	enum class Cooldowns {ROTATE = 10, LEFT_RIGHT = 3, DOWN = 1}; //number of ticks before the player can make an action in the game
	enum class Bot_Level { BEST = 3, GOOD = 2, NOVICE = 1 }; //All the levels of the bot
	enum class Bot_Accuracy {NOVICE = 10, GOOD = 40};

	static constexpr char ESC = 27;
	static constexpr int BOARD_WIDTH = 12;
	static constexpr int BOARD_HEIGHT = 18;  //The Width and Height of the boards in the game
	static constexpr int BLAST_RADIUS = 4; //Blast Radius of the bomb
	static constexpr int BOMB_CHANCE = 20; //The chances for a bomb to spawn (in this case, 1 in 20)
};

