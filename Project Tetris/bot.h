#pragma once
//#include "board.h"
#include "shape.h"
#include "position.h"
#include <cmath>

//Shape that plays itself
class Bot : public Shape
{
    int getHoleCount();
    float getBumpinessLevel(int& maxHeight);
    int getFullLinesCount();
    int fillHeightsArr(int heights[]);
    void updateBestPosition(Position& bestPosition, float score);
public:
    Bot(Board& _board, char ch = -2); 
    void moveToPosition(const Position& bestPosition);
    void findBestPosition(Position& bestPosition);
    float getPositionScore();
};


