#pragma once
//#include "board.h"
#include "shape.h"
#include "position.h"
#include <cmath>

//Shape that plays itself
//#define LEFT 'l'
//#define RIGHT 'r'
class Bot : public Shape
{
    Position bestPosition;
    enum class Action {LEFT, RIGHT, CLOCKWISE, COUNTER_CLOCKWISE};
    const int playerNum = board.getPlayerNum();

    int getHoleCount();
    float getBumpinessLevel(int& maxHeight);
    int getFullLinesCount();
    int fillHeightsArr(int heights[]);
    void updateBestPosition(float score);
    char getInputForAction(Action action);
    int getNextOrientation(int key);
public:
    Bot(Board& _board, char ch = -2); 
    void moveToPosition(const Position& bestPosition);
    void findBestPosition();
    float getPositionScore();
    void takeAction();
    int getOffsetForLeftRight(char input);

};


