#pragma once
#include "Libraries.h"


class GameConfig
{
public:
	enum class P1keys { LEFT = 'a', RIGHT = 'd', CLOCKWISE = 's', COUNTER_CLOCKWISE = 'w', ESC = 27, DOWN = 'x'};
	enum class P2keys { LEFT = 'j', RIGHT = 'l', CLOCKWISE = 'k', COUNTER_CLOCKWISE = 'i', DOWN = 'm' };
	static constexpr int BOARD_WIDTH = 12;
	static constexpr int BOARD_HEIGHT = 18; 
};

