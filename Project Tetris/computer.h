#pragma once
#include "board.h"
#include "shape.h"
#include "position.h"

class Computer : public Shape
{
    int getHoleCount();
    double getBumpinessLevel();
    int getFullLinesCount();
public:
    //Computer(int x, int y, int _playerNum, const Shape& _shape);
    Computer(Board& _board, char ch = -2);
    void findBestPosition(Position& bestPosition);
    float getPositionScore();
    void updateBestPosition(Position& bestPosition, int score);
};


