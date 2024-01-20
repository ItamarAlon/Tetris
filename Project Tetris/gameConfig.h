#pragma once
#include "Libraries.h"

class GameConfig
{
public:
	enum class Lkeys { LEFT = 'a', RIGHT = 'd', CLOCKWISE = 's', COUNTER_CLOCKWISE = 'w', ESC = 27, DOWN = 'x' };
	enum class Rkeys { LEFT = 'j', RIGHT = 'l', CLOCKWISE = 'k', COUNTER_CLOCKWISE = 'i', ESC = 27, DOWN = 'm' };
	//static constexpr int BOARD_WIDTH = 11;
	//static constexpr int BOARD_HEIGHT = 20; //Change dimentions later
};

