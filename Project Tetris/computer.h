#pragma once
#include "board.h"
#include "shape.h"
#include "position.h"

class Computer : public Shape
{
    int getHoleCount();
    int getBumpinessLevel();
    int getFullLinesCount();
public:
    //Computer(int x, int y, int _playerNum, const Shape& _shape);
    Computer(Board& _board, char ch = -2);
    void findBestPosition(Position& bestPosition);
    int getPositionScore();
    void updatePosition(Position& bestPosition, int score);
};


